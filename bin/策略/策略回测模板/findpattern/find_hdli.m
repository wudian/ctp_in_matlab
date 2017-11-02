function signal = find_hdli(daydata, inpara)
%%% 跌中高和涨中低 (设置幅度上下限，成交量过滤)
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价 成交量]
%% inpara{1} = [采样频率 连续涨跌K线数 幅度上限lim_up 幅度下限lim_down 成交量均值倍数m 滑点c]; 
%% inpara{2} = sec_points e.g. [1 75 135 175 215] 
%%
%%% OUTPUT
%% signal.name    =   models{i}.name 
%% signal.inplace =   [ ]         (where to get in) 
%% signal.direct  =   [+1 or -1]   (+1  Buy; -1 Sell)  
%% signal.inprice =   [ ]  

%%% Step 0: INPUT check 
%%% 
freq = inpara{1}(1);   ct = inpara{1}(2); lim_up = inpara{1}(3); lim_down = inpara{1}(4); 
m = inpara{1}(5); c = inpara{1}(6);
len_day = inpara{2}(end);

%%% Step 1: Sampling by 采样频率
sec_points = inpara{2}; %% [1 75 135 175 215];  
n_sample = 0; 
for j = 1 : length(sec_points) - 1
    %% 1.1 sampling from the daydata
    if j == 1
        section{j} = daydata(sec_points(j):sec_points(j+1),:); 
    else
        section{j} = daydata(sec_points(j)+1:sec_points(j+1),:);  
    end
    %% n_sec(i,1) = sec_points(j) - sec_points(j+1);
    [sec{j} sec_num{j}]= sample_k(section{j},freq);
    %% 1.2 collect the sampled data 
    sampled_day_data(n_sample+1 : n_sample+length(sec_num{j}),:) = sec{j};
    sampled_day_data_size(n_sample+1 : n_sample+length(sec_num{j}),1) = sec_num{j}; 
    n_sample = n_sample + length(sec_num{j});
end

%%% Step 2: Find Pattern 
%% 2.1 预先判断
if n_sample <= ct 
    signal = {};
    return; 
end
%% 2.2 寻找连涨连跌及入场搜索起始点
k = 0; %% number of the tcd or tci patterns
l1 = 1; 
for i = 1 : (n_sample-ct-1) 
    if sampled_day_data(i,2) <  sampled_day_data(i+1,2) %% 最高价递增
        l1 = 1;
        for j = i+1:i+ct-1
            if sampled_day_data(j,2) >= sampled_day_data(j+1,2) %% 存在反趋势，则此ct连增不成立
                l1 = 0;break;
            end
        end
        if l1 %% i到i+ct递增
            temp = sampled_day_data(i+ct,2) - sampled_day_data(i,3);   %% ct连增的累计增幅
            ave = sum(sampled_day_data(i:i+ct,5))/(ct+1);  %% ct+1根K线的平均成交量
            if temp <= lim_up  && temp >= lim_down && sampled_day_data(i+ct,5) >= m*ave
                k = k + 1;
                begin(k) = sum(sampled_day_data_size(1:i+ct)) + 1;  %% ct连增后搜索入场的起始点
                inprice(k) = sampled_day_data(i+ct,3) + c; %% 挂单价格
                tmp(k) = 1;                %% 连增卖空 -1
            end
        end
    elseif sampled_day_data(i,3) >  sampled_day_data(i+1,3) %% 最低价递减
        l1 = 1;
        for j = i+1:i+ct-1
            if sampled_day_data(j,3) <= sampled_day_data(j+1,3) %% 存在反趋势，则此ct连减不成立
                l1 =0; break;
            end
        end
        if l1 %% i到i+ct递减
            temp = sampled_day_data(i,3) - sampled_day_data(i+ct,3);   %% ct连减的累计减幅
            ave = sum(sampled_day_data(i:i+ct,5))/(ct+1);  %% ct+1根K线的平均成交量
            if temp <= lim_up  && temp >= lim_down && sampled_day_data(i+ct,5) >= m*ave
                k = k + 1;
                begin(k) = sum(sampled_day_data_size(1:i+ct)) + 1;  %% ct连减后搜索入场的起始点
                inprice(k) = sampled_day_data(i+ct,2) - c; %% 挂单价格
                tmp(k) = -1;               %% 连减买入 +1
            end
        end
    end
end
 
%%% Step 3: 判断是否存在进场点，计算进场点在抽样前数据中的位置(inplace)和价格(inprice)
if k > 0   
   t = 0;
   for i = 1:k
       if tmp(i) == 1
           if daydata(begin(i),3) > inprice(i) && begin(i)~=len_day %% 做多时向上跳空
               t = t+1;
               signal.inplace(t) = begin(i);   %% OUTPUT 2
               signal.direct(t) = tmp(i);      %% OUTPUT 3
               signal.inprice(t) = daydata(begin(i),1);  %% OUTPUT 4
               continue;
           elseif daydata(begin(i),3) <= inprice(i) && daydata(begin(i),2) >= inprice(i) && begin(i)~=len_day 
               t = t+1;
               signal.inplace(t) = begin(i);   %% OUTPUT 2
               signal.direct(t) = tmp(i);      %% OUTPUT 3
               signal.inprice(t) = inprice(i);  %% OUTPUT 4
               continue;
           else
               if i < k
                   for r = (begin(i)+1):begin(i+1)  %% 从下一分钟到新信号的起始搜索点
                       if daydata(r,3) > inprice(i) && r~=len_day %% 做多时向上跳空
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = daydata(r,1);  %% OUTPUT 4
                          break;
                       elseif daydata(r,3) <= inprice(i) && daydata(r,2) >= inprice(i) && r~=len_day
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = inprice(i);  %% OUTPUT 4
                          break;
                       end
                   end
               elseif i == k
                   for r = (begin(k)+1):(len_day-1)
                       if daydata(r,3) > inprice(i) && r~=len_day %% 做多时向上跳空
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = daydata(r,1);  %% OUTPUT 4
                          break;
                       elseif daydata(r,3) <= inprice(i) && daydata(r,2) >= inprice(i) && r~=len_day
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = inprice(i);  %% OUTPUT 4
                          break;
                       end
                   end
               end  %% 第一分钟未入场，向后搜索
           end %% 做多时的三种情况:跳空高开,存在入场价，向后搜索
       
       elseif tmp(i) == -1
           if daydata(begin(i),2) < inprice(i) && begin(i)~=len_day %% 做空时向下跳空
               t = t+1;
               signal.inplace(t) = begin(i);   %% OUTPUT 2
               signal.direct(t) = tmp(i);      %% OUTPUT 3
               signal.inprice(t) = daydata(begin(i),1);  %% OUTPUT 4
               continue;
           elseif daydata(begin(i),2) >= inprice(i) && daydata(begin(i),3) <= inprice(i) && begin(i)~=len_day
               t = t+1;
               signal.inplace(t) = begin(i);   %% OUTPUT 2
               signal.direct(t) = tmp(i);      %% OUTPUT 3
               signal.inprice(t) = inprice(i);  %% OUTPUT 4
               continue;
           else
               if i < k
                   for r = (begin(i)+1):begin(i+1)  %% 从下一分钟到新信号的起始搜索点
                       if daydata(r,2) < inprice(i) && r~=len_day %% 做空时向下跳空
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = daydata(r,1);  %% OUTPUT 4
                          break;
                       elseif daydata(r,2) >= inprice(i) && daydata(r,3) <= inprice(i) && r~=len_day
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);     %% OUTPUT 3
                          signal.inprice(t) = inprice(i);  %% OUTPUT 4
                          break;
                       end
                   end
               elseif i == k
                   for r = (begin(k)+1):(len_day-1)
                       if daydata(r,2) < inprice(i) && r~=len_day %% 做空时向下跳空
                          t = t+1;
                          signal.inplace(t) = r;         %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = daydata(r,1);  %% OUTPUT 4
                          break;
                       elseif daydata(r,2) >= inprice(i) && daydata(r,3) <= inprice(i) && r~=len_day
                          t = t+1;
                          signal.inplace(t) = r;          %% OUTPUT 2
                          signal.direct(t) = tmp(i);      %% OUTPUT 3
                          signal.inprice(t) = inprice(i);  %% OUTPUT 4
                          break;
                       end
                   end
               end  %% 第一分钟未入场，向后搜索
           end %% 做空时的三种情况:跳空高开,存在入场价，向后搜索
       end  %% 做多、做空两种情况
   end          
             
    if t > 0
        signal.name = 'hdli'; %% OUTPUT 1
        return;
    end
    
end %% k > 0

    signal = {}; 
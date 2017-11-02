function record = strategy_signalout_2(todaydata, oper_infos)
%%% 解决对锁问题的简单策略  (综合各独立进、出场信号)
%%  
%%% INPUT
%%  1 daydata   [开盘价 最高价 最低价 收盘价]
%%
%%  2 oper_infors{i} 
%%          .name
%%          .inplace  =  []     VECTOR
%%          .direct   =  []     BOOL +1 or -1
%%          .inprcie  =  []     VECTOR
%%          .outplace =  []     VECTOR
%%          .outprice =  []     VECTOR
%%  3 strategy 
%%          .name = STRING    
%%          .para =  []       e.g.  'simple'  ， +1 or -1 or 0  
%%% OUTPUT
%%  1 record
%%          .rec  = [inplace, inprice, outplace, outprice, direct, profit] 
%%          .name 
%%               (the name of the models for each record.)


%%% Step 0: INPUT Check 
record = {}; 
%%% Step 1: 计算每个模型对应的有几笔交易,将交易笔数不为零的模型信息 ---> oper_temp
n_model = length(oper_infos);    %% 模型数量 
if n_model == 0
    return;
end
if n_model ==1
    if ~isempty(oper_infos{1})
        for k = 1:length(oper_infos{1}.inplace)
        record.name{k} = oper_infos{1}.name;
        record.rec{k,1}  = [oper_infos{1}.inplace(k), oper_infos{1}.inprice(k), oper_infos{1}.outplace(k), oper_infos{1}.outprice(k), ...
                               oper_infos{1}.direct(k), oper_infos{1}.profit(k),oper_infos{1}.bestprice(k), oper_infos{1}.badprice(k),oper_infos{1}.bestpricetime(k), ...
                               oper_infos{1}.badpricetime(k), oper_infos{1}.break(k),oper_infos{1}.goback(k), oper_infos{1}.gobacktime(k)]; 
        end
    end
    return; 
end
    
len_day = size(todaydata,1); 

for i = 1:n_model
    if isempty(oper_infos{i})
       n_rec(i) = 0; 
       num_temp(i) = 0;
    else
       n_rec(i) = length(oper_infos{i}.inplace); %% 每个模型各自的交易数量
       if n_rec(i) > 1  %% 先解决模型内部对锁问题
%            在处理模型间对锁之前，把它处理掉 
             oper_temp{i} = oper_infos{i}; 
%            oper_temp{i_temp} = strategy_single(todaydata, oper_infos{i});
%            %% 涉及提前出场问题 
             num_temp(i) = length(oper_infos{i}.inplace); 
       else
            oper_temp{i} = oper_infos{i};  
            num_temp(i) = n_rec(i); 
       end
    end
end
n_temp = n_model; 

%%% Step 2: 不用寻找起始点，静态变量 direct 标识当前交易的方向
% current = zeros(n_temp,1) ; %% 第几个模型的第几笔交易在进行中 每个模型单独处理之后，这个变量就不需要了

r = 0;      %% number of records
for k = 1:num_temp(1)    % 第 1 个 模型的第 k 笔交易 %% oper_infos{j}.inplace(k)  三模型结构 : 第一个模型是主体模型，第二个用来加仓，第三个用来减仓
    i_pos = 2;       i_neg = 3;   %  三模型结构 : 第一个模型是主体模型，第二个(i_pos)用来加仓，第三个(i_neg)用来减仓
    l_pos = 0;  l_neg = 0;
    %% 寻找在第k条交易过程中出现的加、减仓信号
    for i = 1:n_rec(i_pos) ;
        if oper_temp{i_pos}.inplace(i) > oper_temp{1}.inplace(k)    &&   oper_temp{i_pos}.inplace(i)  < oper_temp{1}.outplace(k)  ...
                && oper_temp{i_pos}.direct(i)*oper_temp{1}.direct(k) > 0
            l_pos = 1;
            break;
        end
    end
    
    for j = 1:n_rec(i_neg) ;
        if oper_temp{i_neg}.inplace(j) > oper_temp{1}.inplace(k)    &&   oper_temp{i_neg}.inplace(j)  < oper_temp{1}.outplace(k)  ...
                && oper_temp{i_neg}.direct(j) * oper_temp{1}.direct(k) < 0
            l_neg = 1;
            break;
        end
    end
    
    % i, j 为finally 搜索到的在主模型进出场过程中出现的加(i)、减(j)仓信号；
    if l_pos && ~l_neg          %% 只有加仓信号
        r = r+1;
        rec_add(r,:) = [oper_temp{i_pos}.inplace(i), oper_temp{i_pos}.inprice(i), oper_temp{1}.outplace(k), oper_temp{1}.outprice(k), oper_temp{i_pos}.direct(i),  (oper_temp{1}.outprice(k)-oper_temp{i_pos}.inprice(i))*oper_temp{i_pos}.direct(i)];    
        rec_rmv(r,:) = [0,0,0,0,0,0];
        rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{1}.outplace(k), oper_temp{1}.outprice(k), ...
            oper_temp{1}.direct(k),  rec_add(r,6) + oper_temp{1}.profit(k) , oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
            oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
        rec_name{r}= oper_temp{1}.name;
        
    elseif  ~l_pos && l_neg   %% 只有减仓信号
        r = r+1;
        rec_add(r,:) = [0,0,0,0,0,0];
        rec_rmv(r,:) =  [oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j),oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), oper_temp{i_neg}.direct(j), 0];
        rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), ...
            oper_temp{1}.direct(k),  oper_temp{1}.direct(k) * (oper_temp{i_neg}.inprice(j) - oper_temp{1}.inprice(k) ), oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
            oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
        rec_name{r}= oper_temp{1}.name;
        
    elseif  l_pos && l_neg    %% 同时有加、减仓信号 
        if  oper_temp{i_pos}.inplace(i) > oper_temp{i_neg}.inplace(j)        %% 减仓信号先出现
            r = r+1;
            rec_add(r,:) = [oper_temp{i_pos}.inplace(i), oper_temp{i_pos}.inprice(i), oper_temp{1}.outplace(k), oper_temp{1}.outprice(k), oper_temp{i_pos}.direct(i),  oper_temp{i_pos}.profit(i)]; 
            rec_rmv(r,:) = [oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j),oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), oper_temp{i_neg}.direct(j), 0];
            rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), ...
                oper_temp{1}.direct(k),  oper_temp{i_pos}.profit(i) + oper_temp{1}.direct(k) * (oper_temp{i_neg}.inprice(j) - oper_temp{1}.inprice(k) ), oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
                oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
            rec_name{r}= oper_temp{1}.name;
        elseif  oper_temp{i_pos}.inplace(i) > oper_temp{i_neg}.inplace(j)   %% 加仓信号先出现
            r = r+1;
            rec_add(r,:) = [oper_temp{i_pos}.inplace(i), oper_temp{i_pos}.inprice(i), oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), oper_temp{i_pos}.direct(i),  oper_temp{i_pos}.direct(i)*(oper_temp{i_neg}.inprice(j)-oper_temp{i_pos}.inprice(i))];
            rec_rmv(r,:) = [oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), oper_temp{i_neg}.direct(j), 0];
            rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{i_neg}.inplace(j), oper_temp{i_neg}.inprice(j), ...
                oper_temp{1}.direct(k),  oper_temp{1}.direct(k) * (2* oper_temp{i_neg}.inprice(j)-oper_temp{i_pos}.inprice(i) - oper_temp{1}.inprice(k) ), oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
                oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
            rec_name{r}= oper_temp{1}.name;     
        else % 同时出现
            r = r+1;
            rec_add(r,:) = [0,0,0,0,0,0];
            rec_rmv(r,:) = [0,0,0,0,0,0];
            rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{1}.outplace(k), oper_temp{1}.outprice(k), ...
                oper_temp{1}.direct(k),  oper_temp{1}.profit(k) , oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
                oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
            rec_name{r}= oper_temp{1}.name;
        end
    else 
       r = r+1;
            rec_add(r,:) = [0,0,0,0,0,0];
            rec_rmv(r,:) = [0,0,0,0,0,0];
            rec(r,:) = [oper_temp{1}.inplace(k), oper_temp{1}.inprice(k), oper_temp{1}.outplace(k), oper_temp{1}.outprice(k), ...
                oper_temp{1}.direct(k),  oper_temp{1}.profit(k) , oper_temp{1}.bestprice(k), oper_temp{1}.badprice(k),oper_temp{1}.bestpricetime(k), ...
                oper_temp{1}.badpricetime(k), oper_temp{1}.break(k),oper_temp{1}.goback(k), oper_temp{1}.gobacktime(k) ]; %% [inplace, inprice, outplace, outprice, direct, profit]
            rec_name{r}= oper_temp{1}.name; 
    end 
end                 
%%% Step 3:     输出交易记录         
if r == 0
    record = {};
    return;
end
for y = 1:r
    record.name{y} = rec_name{y};            %%% OUTPUT
    record.rec{y,1} = rec(y,:);                %% 把记录都输出来，模型名称 操作 
%     record.rec{y,2} = rec_add(y,:); 
%     record.rec{y,3} = rec_rmv(y,:);  
end

%%% OUTPUT
%%  1 record
%%      .rec  = [inplace, inprice, outplace, outprice, direct, profit] 
%%      .name = ''   (which model deduces this record)              
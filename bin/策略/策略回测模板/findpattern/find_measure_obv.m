function signal = find_measure_obv(daydata, inpara) 
%%% 小节模型  (对应区间入场交易，根据分钟累计的OBV进行过滤)
%%% INPUT
%% hisdata : data in yesterday [开盘价 最高价 最低价 收盘价 成交量]
%% daydata : data in today       [开盘价 最高价 最低价 收盘价 成交量]
%% inpara{1} = [区间幅度 滑点 信号窗口起始 信号窗口结束 进场起始 进场结束 OBV阈值下限 OBV阈值上限]; 
%% inpara{2} = sec_points; %% [1 75 135 175 215];
%%
%%% OUTPUT
%% signal.name =            STRING 
%% signal.inplace =  []     VECTOR
%% signal.direct   =  []     BOOL +1 or -1
%% signal.inprcie =  []     VECTOR

%%% Step 0: INPUT check 
%%%  
range = inpara{1}(1);         %  区间幅度
slip = inpara{1}(2);             %  滑点
m = inpara{1}(3);                %  信号窗口起始
n = inpara{1}(4);                 %  信号窗口结束 
p = inpara{1}(5);                 %  进场起始
n = inpara{1}(6);                 %  进场结束
lim_down =  inpara{1}(7);
lim_up = inpara{1}(8);
len_day = inpara{2}(end);  
have =0;

%%% Step 1: judge the range of the day break 
if  daydata(m,1) - daydata(n,4) > range  %% 实体 = m行开盘价 - n行收盘价 
    have = -1;
elseif daydata(n,4) - daydata(m,1) > range
    have = 1;
end

obv =  sum( daydata(m:n,5) .*  (daydata(m:n,4) - daydata(m:n,1) > 0)   -    daydata(m:n,5) .*  (daydata(m:n,4) - daydata(m:n,1) < 0) ) ;      % 正方向 + 负方向 - 1 

%%% Step 2:  Find range break point. 
k = 0; 
    if  have == 1 && obv >= lim_up 
        k = k+1;
        signal.inplace(k) = p;       %% OUTPUT 2 
        signal.direct(k) = +1;       %% OUTPUT 3
        signal.inprice(k) = daydata(p,1) + slip; %% OUTPUT 4
        
    elseif have == -1 && obv <=lim_down
        k = k+1;
        signal.inplace(k) = p;       %% OUTPUT 2 
        signal.direct(k) = -1;        %% OUTPUT 3
        signal.inprice(k) = daydata(p,1) - slip; %% OUTPUT 4   

    end
    
%% Step 3: 统计寻找到的信号 
if k > 0
    signal.name = 'measure_obv';  %% OUTPUT 1 
else
    signal = {}; 
end






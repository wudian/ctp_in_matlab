function signal = find_overleap(hisdata, daydata, inpara) 
%%% 跳空突破 
%%% INPUT
%% hisdata : data in yesterday [开盘价 最高价 最低价 收盘价]
%% daydata : data in today  [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [跳空幅度 滑点 价格最小波动 收盘前n分钟不操作 是否允许多次进场]; %% 
%% inpara{2} = sec_points; %% [1 75 135 175 215];
%%
%%% OUTPUT
%% signal.name =            STRING 
%% signal.inplace =  []     VECTOR
%% signal.direct  =  []     BOOL +1 or -1
%% signal.inprcie =  []     VECTOR

%%% Step 0: INPUT check 
%%%  

range = inpara{1}(1); slip = inpara{1}(2); 
g =  inpara{1}(3); n = inpara{1}(4); 
len_day = inpara{2}(end); 
have = 0;
%%% Step 1: judge the range of the day break 
if  hisdata(215,4) - daydata(1,1) > range  %% 跳空 = 今日开盘价 - 昨日收盘价 (昨日)
    have = 1;
elseif daydata(1,1) - hisdata(215,3) > range
    have = -1;
end
%%% Step 2:  Find range break point. 
hishigh = hisdata(215,2); 
hislow = hisdata(215,3);
k = 0; 
for i = 2:len_day - n
    if daydata(i,2) >= hislow + slip && have == 1 && daydata(i-1,2) < hislow + slip  && daydata(i,3) <= hislow + slip 
        k = k+1;
        signal.inplace(k) = i;       %% OUTPUT 2 
        signal.direct(k) = +1;       %% OUTPUT 3
        signal.inprice(k) = hislow + slip; %% OUTPUT 4
        
    elseif daydata(i,3) <= hishigh - slip && have == -1  &&  daydata(i-1,3) > hishigh - slip && daydata(i,2) >= hislow - slip
        k = k+1;
        signal.inplace(k) = i;       %% OUTPUT 2 
        signal.direct(k) = -1;       %% OUTPUT 3
        signal.inprice(k) = hishigh - slip; %% OUTPUT 4   

    end
    
    if ~inpara{1}(5)  &&  k > 0  %% 一天内是否允许多次进场
        break;
    end
end
%% Step 3: 统计寻找到的信号 
if k > 0
    signal.name = 'overleap_break';  %% OUTPUT 1 
else
    signal = {}; 
 end
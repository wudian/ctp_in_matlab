function signal = find_reversal(daydata, inpara) 
%%% 波幅突破 (一天一次进场？)
%%% INPUT
%% hisdata : data in yesterday [开盘价 最高价 最低价 收盘价]
%% daydata : data in today  [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [做多超出幅度 做空超出幅度]; %% 
%% inpara{2} = sec_points; %% [1 75 135 175 215];
%%
%%% OUTPUT
%% signal.name =            STRING 
%% signal.inplace =  []     VECTOR
%% signal.direct  =  []     BOOL +1 or -1
%% signal.inprcie =  []     VECTOR

%%% Step 0: INPUT check 
%%%  

p1 = inpara{1}(1); p2 = inpara{1}(2); 

len_day = inpara{2}(end); 

%%% Step 1: Compute amplitude 

%%% Step 2:  Find amplitude break point. 

k = 0; 

    if daydata(76,2) - daydata(75,2) >= p1  
        k = k+1;
        signal.inplace(k) = 77;       %% OUTPUT 2 
        signal.direct(k) = -1;       %% OUTPUT 3 +1
        signal.inprice(k) = daydata(77,1); %% OUTPUT 4
        signal.break(k) = 77;
        
    elseif daydata(75,3) - daydata(76,3) >= p2
        k = k+1;
        signal.inplace(k) = 77;       %% OUTPUT 2 
        signal.direct(k) = +1;       %% OUTPUT 3 -1
        signal.inprice(k) = daydata(77,1); %% OUTPUT 4
        signal.break(k) = 77;

    end
    
  
%% Step 3: 统计寻找到的信号 
if k > 0
    signal.name = 'reversal';  %% OUTPUT 1 
else
    signal = {}; 
 end

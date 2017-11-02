function signal = find_outinfo(hisdata, daydata, inpara)
%%% 外盘数据模型 
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = '伦铜数据.xlsx';   %%        e.g. 'tcdtci'  [连发次数 采样频率]
%% inpara{2} = sec_points e.g. [1 75 135 175 215]  or   [1 75 135 225]
%% inpara{3} = [a b g];  %% [开多仓百分比  开空仓百分比  波动率]
%%% OUTPUT
%% signal.name    =   models{i}.name 
%% signal.inplace =   [ ]         (where to get in) 
%% signal.direct  =   [+1 or -1]   (+1  Buy; -1 Sell)  
%% signal.inprice =   [ ]  

global i_day %% 了解当前进行的是第几天的外盘

%% Step 1 : 第一天模型不操作
if i_day ==1 || i_day == length(inpara{1}) / 2 + 1
    signal = {}; 
    return;
end 
i1 =  (i_day-1) * 2 ;
i2 =  (i_day-1) * 2 + 1; 

yes_out = inpara{1}(i1); 
tod_out = inpara{1}(i2);

%% Step 2 : 如果当天没有外盘信息，模型也不操作
if isnan(yes_out) || isnan(tod_out)
        signal = {}; 
end
    
%% Step 3 : 寻找入场信号
len_day = inpara{2}(end); 
a = inpara{3}(1); %% 开多仓百分比 
b = inpara{3}(2); %% 开多仓百分比
g = inpara{3}(3); %% 波动率

amp1 = (tod_out - yes_out) / yes_out;                         %% 国内涨跌幅
amp2 = (daydata(135,4) - hisdata(215,4)) / hisdata(215,4);    %% 国外涨跌幅
amp = max(daydata(:,2)) - min(daydata(:,3)) / daydata(135,4); %% 国内上午振幅
sig = amp1 -amp2; 

if sig > a  &&  amp > g
    signal.name = 'outinfo';
    signal.inplace(1) = 136;
    signal.direct(1) = 1; 
    signal.inprice(1) = daydata(135,4);
    return; 
elseif sig < b  &&  amp > g
    signal.name = 'outinfo';
    signal.inplace(1) = 136;
    signal.direct(1) = -1; 
    signal.inprice(1) = daydata(135,4);
    return;
end

signal = {}; 







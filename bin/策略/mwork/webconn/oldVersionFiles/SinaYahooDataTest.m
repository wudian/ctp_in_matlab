%% SinaYahooDataTest
% by LiYang
% Email:farutoliyang@gmail.com
% 2013/11/26
%% A Little Clean Work
tic;
clear;
clc;
close all;
format compact;
%% 获取历史数据测试

% 历史数据通过Yahoo接口获得 （历史数据为未复权数据，使用时候请注意）
% Yahoo中证券代码为 （上海 .ss 深圳 .sz),例如招商银行，600036.ss

StockName = '600036.ss';
StartDate = today-200;
EndDate = today;
Freq = 'd';
[DataYahoo, Date_datenum, Head]=YahooData(StockName, StartDate, EndDate, Freq);

% K线展示
scrsz = get(0,'ScreenSize');
figure('Position',[scrsz(3)*1/4 scrsz(4)*1/6 scrsz(3)*4/5 scrsz(4)]*3/4);

Open = DataYahoo(:,2);
High = DataYahoo(:,3);
Low = DataYahoo(:,4);
Close = DataYahoo(:,5);
MT_candle(High,Low,Close,Open,[],Date_datenum);
xlim( [0 length(Open)+1] );
title(StockName);
%% 获取实时数据测试
% Sina中证券代码为 （sh. 上海 sz.深圳),例如招商银行sh600036

StockCode='sh600036';
[DataSina, DataCell]=SinaData(StockCode);
DataCell
%% Record Time
toc;
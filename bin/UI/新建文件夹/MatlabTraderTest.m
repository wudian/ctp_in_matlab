%% MatlabTraderTest
% 脚本函数
% Last Modified by LiYang 2011/12/28
% Email:faruto@163.com
% 程序实现测试所使用的MATLAB版本：MATLAB R2011b(7.13)
% 如果程序在您本机运行不了，请首先检查您MATLAB的版本号，推荐使用较新版本的MATLAB。

%% A little clean work
tic;
clear;
clc;
close all;
format compact;
%% Connect to Yahoo! 
Connect = yahoo;
load yhfields.mat;
if isconnection(Connect) == 0
    error('请检查您的网络是否连接正常');
end
%% Get Data from Yahoo
if isconnection(Connect) == 1
    Fields = {'Open';'High';'Low';'Close';'Volume'};
%     FromDate = '2011/9/1';
    ToDate = today;
    datestr(ToDate)
    FromDate = today-252;
    Security = '000300.SS';
    stock = fetch(Connect, Security, Fields, FromDate, ToDate);
    
    stock = stock( end:(-1):1, : );
    
    stockfts = fints(stock(:,1),stock(:,2:end),Fields,'D',Security);
    % Open High Low Close Volume
    stockmat = fts2mat(stockfts);
    date = stockfts.dates;
%% 各种图形展示
% candle 
%% candle蜡烛图
%     figure;
%     % High Low Close Open
%     H = stockmat(:,2);
%     L = stockmat(:,3);
%     C = stockmat(:,4);
%     O = stockmat(:,1);
%     MT_candle(H,L,C,O,[],stockfts.dates);
%% Volume成交量  
    figure;
%     hold on;
%     len = length(stockfts);
%     
%     for i = 1:len
%         if fts2mat(stockfts(i).Close) >= fts2mat(stockfts(i).Open)
%             bar(i,fts2mat(stockfts(i).Volume),'w','EdgeColor','r');
%         else
%             bar(i,fts2mat(stockfts(i).Volume),'g','EdgeColor','g');
%         end
%     end
%     MT_VolumePlot(stockfts);
%% MACD指标
    figure;
    hold on;
    MT_MACD(stockfts);




end


%% Record Time
toc;
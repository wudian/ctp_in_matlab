function MT_MACD(stockfts,short,long,Mlen)
% 函数程序
% MACD图形展示
% Last Modified by LiYang 2011/12/29
% Email:faruto@163.com
% 程序实现测试所使用的MATLAB版本：MATLAB R2011b(7.13)
% 如果程序在您本机运行不了，请首先检查您MATLAB的版本号，推荐使用较新版本的MATLAB。
%% 输入参数检查
error(nargchk(1, 4, nargin))
if nargin < 4
    Mlen = 9;
end
if nargin < 3
    long = 26;
end
if nargin < 2
    short = 12;
end
%% 计算
Close = fts2mat(stockfts.Close);
DIFF = EMA(Close, short)-EMA(Close, long);
DEA = EMA(DIFF, Mlen);

MACDbar = 2*(DIFF-DEA);

%% Plot
hold on;
pind = find(MACDbar >= 0);
nind = find(MACDbar < 0);
h1 = bar(pind,MACDbar(pind),'r','EdgeColor','r','LineWidth',0.1);
h2 = bar(nind,MACDbar(nind),'g','EdgeColor','g','LineWidth',0.1);

plot(DIFF,'k');
plot(DEA,'b');

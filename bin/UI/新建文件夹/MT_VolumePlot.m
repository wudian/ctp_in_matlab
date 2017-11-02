function MT_VolumePlot(stockfts)
% 函数程序
% 成交量图形展示
% Last Modified by LiYang 2011/12/29
% Email:faruto@163.com
% 程序实现测试所使用的MATLAB版本：MATLAB R2011b(7.13)
% 如果程序在您本机运行不了，请首先检查您MATLAB的版本号，推荐使用较新版本的MATLAB。
%%
len = length(stockfts);

for i = 1:len
    if fts2mat(stockfts(i).Close) >= fts2mat(stockfts(i).Open)
        bar(i,fts2mat(stockfts(i).Volume),'w','EdgeColor','r');
        hold on;
    else
        bar(i,fts2mat(stockfts(i).Volume),'g','EdgeColor','g');
        hold on;
    end
end

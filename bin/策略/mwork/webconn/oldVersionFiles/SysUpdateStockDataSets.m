function [Name,CurrentStockData]=SysUpdateStockDataSets(StockCode)
if(StockCode==999999)
symbol=strcat('sh000001');
elseif(StockCode>=600000)%symbol='sz000415' 'sh600000';
symbol=strcat('sh',num2str(StockCode,'%06d'));
else
symbol=strcat('sz',num2str(StockCode,'%06d'));
end
url2Read=['http://hq.sinajs.cn/list=',symbol];
s=urlread(url2Read);
result=textscan(s,'%s','delimiter', ',');
result=result{1};
Name=cell2mat(result(1));%名称
Name=Name(22:end);
OpenPrice=str2double(result{2});% 今日开盘价；
TPrice=str2double(result{4});% 当前价格；
HighPrice=str2double(result{5});% 当前最高价格；
LowPrice=str2double(result{6});%当前最低价格
Vol=str2double(result{9});%成交量
CurrentStockData=single([today,OpenPrice,HighPrice,LowPrice,TPrice,Vol,0]);
end


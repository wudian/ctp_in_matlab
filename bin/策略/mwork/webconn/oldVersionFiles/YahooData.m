function [Data, Date_datenum, Head]=YahooData(StockName, StartDate, EndDate, Freq)
% by LiYang(faruto) @http://www.matlabsky.com
% 本函数是基于 ariszheng @http://www.ariszheng.com/ 的相关函数进行修改而成
% 用来通过Yahoo获取股票历史数据
% 历史数据通过Yahoo接口获得 （历史数据为未复权数据，使用时候请注意）
%% 输入参数
% StockName 证券代码（上海 .ss 深圳 .sz)
% StartDate, EndDate 时间段的开始日与结束日
% Freq 频率
%% 测试函数
% StockName = '600036.ss';
% StartDate = today-200;
% EndDate = today;
% Freq = 'd';
% [DataYahoo, Date_datenum, Head]=YahooData(StockName, StartDate, EndDate, Freq);

%% 数据时间区间
startdate=StartDate;
enddate=EndDate;
%字符串变化
ms=num2str(str2double(datestr(startdate, 'mm'))-1);
ds=datestr(startdate, 'dd');
ys=datestr(startdate, 'yyyy');
me=num2str(str2double(datestr(enddate, 'mm'))-1);
de=datestr(enddate, 'dd');
ye=datestr(enddate, 'yyyy');

% s: 股票代码 (e.g. 002036.SZ 300072.SZ 600036.SS 等)
% c-a-b: 起始日期年、月、日 (月份的起始索引为0) 2010-5-11 = 2010年6月11日
% f-d-e: 结束日期年、月、日 (月份的起始索引为0) 2010-7-23 = 2010年8月23日
% g: 时间周期。d=每日，w=每周，m=每月，v=只返回除权数据
% 省略所有参数，只制定股票代码时，返回所有历史数据
url2Read=sprintf(...
    'http://ichart.finance.yahoo.com/table.csv?s=%s&a=%s&b=%s&c=%s&d=%s&e=%s&f=%s&g=%s&ignore=.csv', StockName, ms, ds, ys, me, de, ye, Freq);

s=urlread_General(url2Read);

Head = ['Date Open High Low Close Volume AdjClose'];
Result=textscan(s, '%s %s %s %s %s %s %s', 'delimiter', ',');

temp = Result{1,1};
Date_datestr = temp(2:end);
Date_datestr = Date_datestr(end:(-1):1);

temp = Result{1,2};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
Open = temp;

temp = Result{1,3};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
High = temp;

temp = Result{1,4};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
Low = temp;

temp = Result{1,5};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
Close = temp;

temp = Result{1,6};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
Volume = temp;

temp = Result{1,7};
temp = cellfun(@str2double, temp(2:end));
temp = temp(end:(-1):1);
AdjClose = temp;

Date_datenum = datenum(Date_datestr);
Date_double = str2num( datestr(Date_datenum, 'yyyymmdd') );

Data = [Date_double, Open, High, Low, Close, Volume, AdjClose];

end
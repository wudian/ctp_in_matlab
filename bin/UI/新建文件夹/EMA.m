function EMAvalue = EMA(Price, len, coef)
% 指数移动平均线 函数
% Last Modified by LiYang 2011/12/27
% Email:faruto@163.com
% 程序实现测试所使用的MATLAB版本：MATLAB R2011b(7.13)
% 如果程序在您本机运行不了，请首先检查您MATLAB的版本号，推荐使用较新版本的MATLAB。

%% 输入参数检查
error(nargchk(1, 3, nargin))
if nargin < 3
    coef = [];
end
if nargin< 2
    len = 2;
end
%% 指定EMA系数
if isempty(coef)
    k = 2/(len + 1);
else
    k = coef;
end
%% 计算EMAvalue
EMAvalue = zeros(length(Price), 1);
EMAvalue(1:len-1) = Price(1:len-1);

for i = len:length(Price)
    
    EMAvalue(i) = k*( Price(i)-EMAvalue(i-1) ) + EMAvalue(i-1);
    
end

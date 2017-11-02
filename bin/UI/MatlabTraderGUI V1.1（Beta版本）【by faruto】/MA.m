function MA_value = MA(Price, MAlen)
% 移动平均线
% by liyang 2011/12/13
% farutoliyang@gmail.com
% Input:
%       Price: 输入的序列
%       MAlen: 均线周期
% Output:
%       MA_value: 计算的均线返回值

%% 输入参数检查
if nargin < 2
    % 默认均线周期为5（5分钟线、5日线）
    MAlen = 5;
end
error(nargchk(1, 2, nargin));
if MAlen <= 0
    error('The length of MA must >= 1');
end
%% 初始化
len = numel(Price);
MA_value = zeros(len, 1);
Price = Price(:);
%% 计算均线
MA_value(1:MAlen-1) = Price(1:MAlen-1);
for i = MAlen:len
     MA_value(i) = sum( Price(i-MAlen+1:i) )/MAlen;
end
%% 
if nargout == 0
    figure;
    hold on;
    plot(Price);
    plot(MA_value, 'r');
    grid on;
    str = ['MA',num2str(MAlen)];
    legend('Price', str);
    hold off;
end

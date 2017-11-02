function  Unsubscribe(Instruments , Period)
% 取消行情的订阅。  如果instruments为空，则取消所有行情的订阅。

global md;

if nargin == 0
    md.Unsubscribe('all', 'all');
    return;
elseif nargin == 1
    md.Unsubscribe(Instruments, 'all');
    return;
else
    md.Unsubscribe(Instruments, Period);
end


end


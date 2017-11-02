function Subscribe(Instruments , Period)
%订阅实时行情
%<param name="Instruments" type="char">合约代码.例如 'IF1406,IF1408,IF1409'.默认'all'</param>
%<param name="Period" type="char">周期.例如'tick','6s','8m','1h'.默认'tick'</param>
%例子 
%Subscribe('IF1409,IF1410', 'tick,6s')
%Subscribe('all', '5s')

global md;
inst = 'all';
per = 'tick';
if nargin == 0
    md.Subscribe(inst, per);
    return;
elseif nargin == 1
    md.Subscribe(Instruments, per);
    return;
else
    md.Subscribe(Instruments, Period);
end

end
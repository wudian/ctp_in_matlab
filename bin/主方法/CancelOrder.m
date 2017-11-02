function CancelOrder(Instrument, Direction, OffsetFlag)
%撤单
%<param name="Instrument" type="char">合约代码.</param>
%<param name="Direction" type="char">买卖方向.只有'Buy'和'Sell'两个可选.</param>
%<param name="OffsetFlag" type="char">开平标志.可选的有'Open'、'Close'(非上期所：平仓)、'CloseToday'（上期所：平今）、'CloseYesterday'（上期所：平昨）.</param>

global td;
if nargin == 0
    td.CancelOrder('', '', '');
elseif nargin == 1
        td.CancelOrder(Instrument, '', '');
elseif nargin >= 2
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
    if strcmpi(Direction, 'Buy')
        direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
    elseif strcmpi(Direction, 'Sell')
        direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Sell;
    else
        direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.NIL;
    end
    if nargin == 2
        td.CancelOrder(Instrument, direction, '');
    else
        td.CancelOrder(Instrument, direction, OffsetFlag);
    end
end

end
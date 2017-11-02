function OrderSysIDs = QryOrder(AllorAvailable, Instrument, Direction, OffsetFlag)
%查报单
%<return name="OrderSysIDs" type="cell">报单编号集合</return>
%<param name="AllorAvailable" type="char">查所有报单还是查可用单.只有'All'和'Available'可选</param>
%<param name="Instrument" type="char">合约代码.为''查所有</param>
%<param name="Direction" type="char">买卖方向.只有'Buy'和'Sell'两个可选.为''查所有</param>
%<param name="OffsetFlag" type="char">开平标志.可选的有'Open'、'Close'(非上期所：平仓)、'CloseToday'（上期所：平今）、'CloseYesterday'（上期所：平昨）.为''查所有</param>
%{
if nargin ~= 4
    error('参数个数有误');
end

order_type = QuantBox.CSharp2CTP.OrderType.E_all;
if ~strcmpi(AllorAvailable, 'All')
    order_type = QuantBox.CSharp2CTP.OrderType.E_available;
end

direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
if strcmpi(Direction, 'Buy')
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
elseif strcmpi(Direction, 'Sell')
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Sell;
else
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.NIL;
end

global td;
OrderSysIDs = td.QueryOrder(order_type, Instrument, direction, OffsetFlag);
%}
end


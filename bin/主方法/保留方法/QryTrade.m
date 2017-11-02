function TradeSysIDs = QryTrade(Instrument, Direction, OffsetFlag)
%查报单
%<return name="TradeSysIDs" type="cell">报单编号集合</return>
%<param name="Instrument" type="char">合约代码.为''查所有</param>
%<param name="Direction" type="char">买卖方向.只有'Buy'和'Sell'两个可选.为''查所有</param>
%<param name="OffsetFlag" type="char">开平标志.可选的有'Open'、'Close'(非上期所：平仓)、'CloseToday'（上期所：平今）、'CloseYesterday'（上期所：平昨）.为''查所有</param>
%{
if nargin ~= 3
    error('参数个数有误');
end

direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
if strcmpi(Direction, 'Buy')
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
elseif strcmpi(Direction, 'Sell')
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Sell;
else
    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.NIL;
end

offset_flag = QuantBox.CSharp2CTP.TThostFtdcOffsetFlagType.NIL;
if strcmpi(OffsetFlag, 'Open')
    offset_flag = QuantBox.CSharp2CTP.TThostFtdcOffsetFlagType.Open;
elseif strcmpi(OffsetFlag, 'Close')
    offset_flag = QuantBox.CSharp2CTP.TThostFtdcOffsetFlagType.Close;
elseif strcmpi(OffsetFlag, 'CloseToday')
    offset_flag = QuantBox.CSharp2CTP.TThostFtdcOffsetFlagType.CloseToday;
elseif strcmpi(OffsetFlag, 'CloseYesterday')
    offset_flag = QuantBox.CSharp2CTP.TThostFtdcOffsetFlagType.CloseYesterday;
end
       
global td;
TradeSysIDs = td.QueryTrade(Instrument, direction, offset_flag);
%}
end


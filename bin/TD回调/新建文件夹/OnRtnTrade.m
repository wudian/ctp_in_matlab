function OnRtnTrade(~, arg)
%成交响应

str = sprintf('成交响应:交易所代码(%s),成交编号(%s),报单编号(%s)', char(arg.pTrade.ExchangeID), char(arg.pTrade.TradeID), char(arg.pTrade.OrderSysID));
disp(str);

end

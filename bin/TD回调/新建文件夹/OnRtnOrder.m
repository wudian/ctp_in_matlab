function OnRtnOrder(~, arg)
%报单响应，一般表明委托成功提交给力交易所
    
str = sprintf('报单响应: 本地报单编号(%s),合约代码(%s),交易所代码(%s),报单编号(%s),报单提交状态(%s),报单状态(%s),状态信息(%s)',char(arg.pOrder.OrderLocalID),char(arg.pOrder.InstrumentID), char(arg.pOrder.ExchangeID), char(arg.pOrder.OrderSysID), char(arg.pOrder.OrderSubmitStatus), char(arg.pOrder.OrderStatus),char(arg.pOrder.StatusMsg));
disp(str);

end
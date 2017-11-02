function  OnErrRtnOrderAction( ~,  arg)
%撤单有误

str = sprintf('撤单失败：错误代码(%d),错误信息(%s),合约代码(%s),报单引用(%s)', arg.pRspInfo.ErrorID, char(arg.pRspInfo.ErrorMsg), char(arg.pInputOrder.InstrumentID), char(arg.pInputOrder.OrderRef));
disp(str)

end


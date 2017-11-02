function  OnRspOrderAction( ~, arg )
%撤单错误

str = sprintf('撤单错误: 合约代码(%s),报单引用(%s),错误(%s)', char(arg.pInputOrderAction.InstrumentID), char(arg.pInputOrderAction.OrderRef), char(arg.pRspInfo.ErrorMsg));
disp(str)

end


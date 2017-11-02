function  OnRspOrderInsert( ~, arg )
%报单错误

str = sprintf('报单错误: 合约代码(%s),报单引用(%s),错误(%s)', char(arg.pInputOrder.InstrumentID), char(arg.pInputOrder.OrderRef), char(arg.pRspInfo.ErrorMsg));
disp(str)

end


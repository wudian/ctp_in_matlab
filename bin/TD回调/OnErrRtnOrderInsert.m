function OnErrRtnOrderInsert( ~, arg )
%报单录入错误回报   （这个接口好像没被调用

str = sprintf('报单录入错误回报: 错误代码(%d),错误信息(%s)；合约代码(%s),报单引用(%s),GTD日期(%s)', arg.pRspInfo.ErrorID, char(arg.pRspInfo.ErrorMsg), char(arg.pInputOrder.InstrumentID), char(arg.pInputOrder.OrderRef), char(arg.pInputOrder.GTDDate));
disp(str);

end


function OnRspQryInvestorPositionDetail( ~ ,arg )
%查询投资者持仓明细响应

str = sprintf('查询投资者持仓明细响应: 合约代码(%s),开仓日期(%s),成交编号(%s),Volume(%d),开仓价(%f)', arg.pInvestorPositionDetail.InstrumentID, arg.pInvestorPositionDetail.OpenDate, arg.pInvestorPositionDetail.TradeID, arg.pInvestorPositionDetail.Volume,arg.pInvestorPositionDetail.OpenPrice);
disp(str)

end


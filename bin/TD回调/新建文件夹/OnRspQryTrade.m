function  OnRspQryTrade( ~, arg )
%查成交响应

if arg.pRspInfo.ErrorID == 0
    str = sprintf('合约代码(%s),报单引用(%s),成交编号(%s),报单编号(%s),成交时间(%s %s)', char(arg.pTrade.InstrumentID), char(arg.pTrade.OrderRef), char(arg.pTrade.TradeID), char(arg.pTrade.OrderSysID), char(arg.pTrade.TradeDate), char(arg.pTrade.TradeTime));
    disp(str);
    if arg.bIsLast == true
        ReqQryInvestorPosition(char(arg.pTrade.InstrumentID)); % 重新查持仓
        disp('查询成交完成'); 
    end
else
    str = sprintf('查成交失败:%s', arg.pRspInfo.ErrorMsg);
    disp(str);
end

end
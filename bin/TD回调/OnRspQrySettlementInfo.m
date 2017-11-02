function  OnRspQrySettlementInfo(~, arg)
%查结算响应

if arg.pRspInfo.ErrorID == 0
    str = sprintf('交易日(%s),结算编号(%d),消息正文(%s)', char(arg.pSettlementInfo.TradingDay), arg.pSettlementInfo.SettlementID, char(arg.pSettlementInfo.Content));
    disp(str);
else
    str = sprintf('查结算失败:%s', arg.pRspInfo.ErrorMsg);
    disp(str);
end

end


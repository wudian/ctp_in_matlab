function OnRtnTrade(~, arg)
%成交响应

    if strcmp(strtrim(char(arg.pTrade.OrderSysID)), '') || strcmp(strtrim(char(arg.pTrade.TradeID)), '')
        return;
    end
    str = sprintf('合约(%s),报单引用(%s),成交编号(%s),报单编号(%s),成交时间(%s %s)', char(arg.pTrade.InstrumentID), char(arg.pTrade.OrderRef), char(arg.pTrade.TradeID), char(arg.pTrade.OrderSysID), char(arg.pTrade.TradeDate), char(arg.pTrade.TradeTime));
    disp(str);
    
    Types;
    InstrumentID = char(arg.pTrade.InstrumentID);
    if (arg.pTrade.Direction == QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy)
        % 买单
        if strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '0') %Open
            TradeHands_BuyOpen.InstrumentID = TradeHands_BuyOpen.InstrumentID + arg.pTrade.Volume;
        elseif strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '1') %Close
            TradeHands_BuyClose.InstrumentID = TradeHands_BuyClose.InstrumentID + arg.pTrade.Volume;
        elseif strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '3') %CloseToday
            TradeHands_BuyCloseToday.InstrumentID = TradeHands_BuyCloseToday.InstrumentID + arg.pTrade.Volume;
        end
    else
        % 卖单
        if strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '0') %Open
            TradeHands_SellOpen.InstrumentID = TradeHands_SellOpen.InstrumentID + arg.pTrade.Volume;
        elseif strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '1') %Close
            TradeHands_SellClose.InstrumentID = TradeHands_SellClose.InstrumentID + arg.pTrade.Volume;
        elseif strcmpi(strtrim(char(arg.pTrade.OffsetFlag)), '3') %CloseToday
            TradeHands_SellCloseToday.InstrumentID = TradeHands_SellCloseToday.InstrumentID + arg.pTrade.Volume;
        end
    end
        
end

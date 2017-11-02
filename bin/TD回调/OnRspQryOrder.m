function  OnRspQryOrder( ~, arg )
%查委托响应

if arg.pRspInfo.ErrorID == 0
    if strcmp(strtrim(char(arg.pOrder.OrderSysID)), '')
        return;
    end
    
    Types;
    InstrumentID = char(arg.pOrder.InstrumentID);
       
    if arg.pOrder.OrderStatus ~= QuantBox.CSharp2CTP.TThostFtdcOrderStatusType.PartTradedNotQueueing &&... % 部分成交不在队列中
        arg.pOrder.OrderStatus ~= QuantBox.CSharp2CTP.TThostFtdcOrderStatusType.Canceled &&... % 撤单
        arg.pOrder.OrderStatus ~= QuantBox.CSharp2CTP.TThostFtdcOrderStatusType.AllTraded % 全部成交
        % 可用报单
        if (arg.pOrder.Direction == QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy)
            % 买单
            if strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '0') %Open
                AvailableOrderHands_BuyOpen.InstrumentID = AvailableOrderHands_BuyOpen.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '1') %Close
                AvailableOrderHands_BuyClose.InstrumentID = AvailableOrderHands_BuyClose.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '3') %CloseToday
                AvailableOrderHands_BuyCloseToday.InstrumentID = AvailableOrderHands_BuyCloseToday.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            end
        else
            % 卖单
            if strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '0') %Open
                AvailableOrderHands_SellOpen.InstrumentID = AvailableOrderHands_SellOpen.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '1') %Close
                AvailableOrderHands_SellClose.InstrumentID = AvailableOrderHands_SellClose.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '3') %CloseToday
                AvailableOrderHands_SellCloseToday.InstrumentID = AvailableOrderHands_SellCloseToday.InstrumentID + arg.pOrder.VolumeTotalOriginal;
            end
        end
    elseif arg.pOrder.OrderStatus ~= QuantBox.CSharp2CTP.TThostFtdcOrderStatusType.Canceled ||... % 撤单
            arg.pOrder.OrderStatus ~= QuantBox.CSharp2CTP.TThostFtdcOrderStatusType.AllTraded % 全部成交
        if (arg.pOrder.Direction == QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy)
            % 买单
            if strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '0') %Open
                AvailableOrderHands_BuyOpen.InstrumentID = AvailableOrderHands_BuyOpen.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '1') %Close
                AvailableOrderHands_BuyClose.InstrumentID = AvailableOrderHands_BuyClose.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '3') %CloseToday
                AvailableOrderHands_BuyCloseToday.InstrumentID = AvailableOrderHands_BuyCloseToday.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            end
        else
            % 卖单
            if strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '0') %Open
                AvailableOrderHands_SellOpen.InstrumentID = AvailableOrderHands_SellOpen.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '1') %Close
                AvailableOrderHands_SellClose.InstrumentID = AvailableOrderHands_SellClose.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            elseif strcmpi(strtrim(char(arg.pOrder.CombOffsetFlag)), '3') %CloseToday
                AvailableOrderHands_SellCloseToday.InstrumentID = AvailableOrderHands_SellCloseToday.InstrumentID - arg.pOrder.VolumeTotalOriginal;
            end
        end
    end

    
    str = sprintf('合约(%s)交易所代码(%s)报单编号(%s)报单提交状态(%s)报单状态(%s)状态信息(%s)', char(arg.pOrder.ExchangeInstID), char(arg.pOrder.ExchangeID), char(arg.pOrder.OrderSysID), char(arg.pOrder.OrderSubmitStatus), char(arg.pOrder.OrderStatus), char(arg.pOrder.StatusMsg));
    disp(str);
    if arg.bIsLast == true
        disp('查询委托完成'); 
    end
else
    str = sprintf('查委托失败:%s', char(arg.pRspInfo.ErrorMsg));
    disp(str);
end

end


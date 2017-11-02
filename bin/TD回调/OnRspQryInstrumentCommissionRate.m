function OnRspQryInstrumentCommissionRate( ~, arg )
%请求查询合约手续费率响应

if arg.pRspInfo.ErrorID ~= 0
    str = sprintf('查询合约手续费率失败：%s', arg.pRspInfo.ErrorMsg);
    disp(str);
    return;
end

str = sprintf('开仓手续费率(%f),平仓手续费率(%f),平今手续费率(%f)', arg.pInstrumentCommissionRate.OpenRatioByMoney, arg.pInstrumentCommissionRate.CloseRatioByMoney, arg.pInstrumentCommissionRate.CloseTodayRatioByMoney);
disp(str);

if arg.bIsLast == true
   str = sprintf('查询合约%s手续费率完成', char(arg.pInstrumentCommissionRate.InstrumentID));
    disp(str);
end




end


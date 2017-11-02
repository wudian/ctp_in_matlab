function  OnRspQryInstrumentMarginRate( ~, arg )
%请求查询合约保证金率响应

if arg.pRspInfo.ErrorID ~= 0
    str = sprintf('查询合约保证金率失败：%s', arg.pRspInfo.ErrorMsg);
    disp(str);
    return;
end

str = sprintf('合约代码(%s), 多头保证金率(%f),空头保证金率(%f)', char(arg.pInstrumentMarginRate.InstrumentID), arg.pInstrumentMarginRate.LongMarginRatioByMoney,arg.pInstrumentMarginRate.ShortMarginRatioByMoney);
disp(str);

if arg.bIsLast == true
   str = sprintf('查询合约%s保证金率完成', char(arg.pInstrumentMarginRate.InstrumentID));
    disp(str);
end


end


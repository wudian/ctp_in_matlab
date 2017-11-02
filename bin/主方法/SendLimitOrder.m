function SendLimitOrder(Instrument, LimitPrice, Direction, OffsetFlag, VolumeTotalOriginal)
%开平仓：限价单
%<param name="Instrument" type="char">合约代码.例如 'IF1406'等</param>
%<param name="LimitPrice" type="double">限价</param>
%<param name="Direction" type="char">买卖方向.只有'Buy'和'Sell'两个可选</param>
%<param name="OffsetFlag" type="char">开平标志.可选的有'Open'、'Close'(非上期所：平仓)、'CloseToday'（上期所：平今）、'CloseYesterday'（上期所：平昨）</param>
%<param name="VolumeTotalOriginal" type="int">数量</param>
%举例：
% SendLimitOrder('IF1409', 2175, 'buy', 'Open', 2)

    direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
    if strcmpi(Direction, 'buy')
        direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Buy;
    elseif strcmpi(Direction, 'sell')
        direction = QuantBox.CSharp2CTP.TThostFtdcDirectionType.Sell;
    else
        error('请指定正确的买卖方向：char类型，只有"Buy"和"Sell"两个可选');
    end
    
    offset_flag = '0';
    if strcmpi(OffsetFlag, 'open')
        offset_flag = '0';
    elseif strcmpi(OffsetFlag, 'close')
        offset_flag = '1';
    elseif strcmpi(OffsetFlag, 'closetoday')
        offset_flag = '3';
    elseif strcmpi(OffsetFlag, 'closeyesterday')
        offset_flag = '4';
    else
        error('请指定正确的开平标志:char类型，可选的有"Open"、"Close"、"CloseToday"、"CloseYesterday"');
    end

    global td;
    nRet = td.SendOrder(...
        -1,... %强行指定报单引用,-1表示由底层生成
        Instrument,... %合约
        direction,... %买卖
        offset_flag,... %开平标记
        '1',... %投机套保标记,指定为投机
        VolumeTotalOriginal,... %数量
        LimitPrice,... %价格
        QuantBox.CSharp2CTP.TThostFtdcOrderPriceTypeType.LimitPrice,... %价格类型：限价
        QuantBox.CSharp2CTP.TThostFtdcTimeConditionType.GFD,... %时间类型：当日有效
        QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.Immediately,... %触发条件类型:立即
        0,... % 止损价
        QuantBox.CSharp2CTP.TThostFtdcVolumeConditionType.AV); %成交量类型
    
    if nRet < 0
       disp('报单提交到CTP服务器就失败了'); 
    end
end

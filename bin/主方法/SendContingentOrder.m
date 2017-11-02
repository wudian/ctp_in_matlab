function SendContingentOrder(Instrument, LimitPrice, Direction, OffsetFlag, VolumeTotalOriginal, ContingentCondition, StopPrice)
%开平仓：触发单/条件单
%<param name="Instrument" type="char">合约代码.例如 'IF1406'等</param>
%<param name="LimitPrice" type="double">下单价格：仅当下单类型为'LimitPrice'时有效</param>
%<param name="Direction" type="char">买卖方向.只有'Buy'和'Sell'两个可选</param>
%<param name="OffsetFlag" type="char">开平标志.可选的有'Open'、'Close'(非上期所：平仓)、'CloseToday'（上期所：平今）、'CloseYesterday'（上期所：平昨）</param>
%<param name="VolumeTotalOriginal" type="int">数量</param>
%<param name="ContingentCondition" type="int">触发条件类型,可选的有 1：立即 2:止损 3:止赢 4：预埋单 5:最新价大于条件价 6:最新价大于等于条件价 7:最新价小于条件价 8:最新价小于等于条件价 9:卖一价大于条件价 10:卖一价大于等于条件价 
                                                                    % 11:卖一价小于条件价 12:卖一价小于等于条件价 13:买一价大于条件价 14:买一价大于等于条件价 15:买一价小于条件价 16:买一价小于等于条件价</param>
%<param name="StopPrice" type="double">止损价</param>
%举例：
% SendContingentOrder('IF1412', 2000, 'sell', 'open', 3, 1, 2100);

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

    contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.Immediately;
    if ContingentCondition == 1
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.Immediately;
    elseif ContingentCondition == 2
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.Touch;
    elseif ContingentCondition == 3
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.TouchProfit;
    elseif ContingentCondition == 4
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.ParkedOrder;
    elseif ContingentCondition == 5
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.LastPriceGreaterThanStopPrice;
    elseif ContingentCondition == 6
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.LastPriceGreaterEqualStopPrice;
    elseif ContingentCondition == 7
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.LastPriceLesserThanStopPrice;
    elseif ContingentCondition == 8
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.LastPriceLesserEqualStopPrice;
    elseif ContingentCondition == 9
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.AskPriceGreaterThanStopPrice;
    elseif ContingentCondition == 10
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.AskPriceGreaterEqualStopPrice;
    elseif ContingentCondition == 11
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.AskPriceLesserThanStopPrice;
    elseif ContingentCondition == 12
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.AskPriceLesserEqualStopPrice;
    elseif ContingentCondition == 13
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.BidPriceGreaterThanStopPrice;
    elseif ContingentCondition == 14
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.BidPriceGreaterEqualStopPrice;
    elseif ContingentCondition == 15
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.BidPriceLesserThanStopPrice;    
    elseif ContingentCondition == 16
        contingent_condition = QuantBox.CSharp2CTP.TThostFtdcContingentConditionType.BidPriceLesserEqualStopPrice;  
    else
        error('请输入合法的触发条件类型');
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
        QuantBox.CSharp2CTP.TThostFtdcOrderPriceTypeType.LimitPrice,... %下单类型：限价
        QuantBox.CSharp2CTP.TThostFtdcTimeConditionType.GFD,... %有效期类型：当日有效
        contingent_condition,...
        StopPrice,... % 止损价
        QuantBox.CSharp2CTP.TThostFtdcVolumeConditionType.AV); %成交量类型
    
    if nRet < 0
       disp('报单提交到CTP服务器就失败了'); 
    end
end

%备份
%<param name="OrderPriceType" type="char">下单类型，可选的有'AnyPrice'、'LimitPrice'、'LastPrice'、'BidPrice1'、'AskPrice1'</param>
%<param name="VolumeCondition" type="char">成交量类型:"AV"表示任何数量，"MV"表示最小数量，"CV"表示全部数量</param>
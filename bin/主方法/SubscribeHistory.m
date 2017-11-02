function SubscribeHistory(Instruments, Period, beginTime, endTime)
%订阅历史数据
%<param name="Instruments" type="char">合约代码.例如 'IF1406,IF1408,IF1409'等</param>
%<param name="Period" type="char">订阅的行情的级别,有'Tick1','Second10','Minute1','Minute5','Minute15','Minute30'等可选</param>
%<param name="beginTime" type="char">模仿'20140804 10:00:00'书写</param>
%<param name="endTime" type="char">模仿'20140804 11:00:00'书写</param>
%举例：
% SubscribeHistory('IF1408', 'Tick1', '20140804 10:50:00', '20140804 11:00:00');

    import QuantBox.CSharp2CTP.*;
    barLen = BarLength.Tick1;
    if strcmpi(Period, 'tick1')
        barLen = BarLength.Tick1;
    elseif strcmpi(Period, 'second10')
        barLen = BarLength.Second10;
    elseif strcmpi(Period, 'Minute1')
        barLen = BarLength.Minute1;
    elseif strcmpi(Period, 'Minute5')
        barLen = BarLength.Minute5;
    elseif strcmpi(Period, 'Minute15')
        barLen = BarLength.Minute15;
    elseif strcmpi(Period, 'Minute30')
        barLen = BarLength.Minute30;
    else
        error('订阅的行情的级别,有"Tick1","Second10","Minute1","Minute5","Minute15","Minute30"等可选');
    end
    
    global KLineOfAllInstruments;
    KLineOfAllInstruments = setfield(KLineOfAllInstruments, Instruments, {});
    global md;
    md.SubscribeHistory(Instruments, barLen, beginTime, endTime);
end

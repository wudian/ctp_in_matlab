function OnMdHistoryKLine( ~, arg )
%
    str1 = sprintf('%s(%s)(%f %f %f %f)', char(arg.pKLine.InstrumentID), char(arg.pKLine.ExchangeTime), arg.pKLine.OpenPrice, arg.pKLine.HighestPrice, arg.pKLine.LowestPrice, arg.pKLine.ClosePrice);
    disp(str1);
    global KLineOfAllInstruments;
    InstrumentID = char(arg.pKLine.InstrumentID);
    lineNum = 0;
    if size(KLineOfAllInstruments.IF1408, 2) ~= 0
       lineNum =   size(KLineOfAllInstruments.IF1408{1},1);
    end
    
    %klineOfInstrumentID = getfield(KLineOfAllInstruments, InstrumentID);
    if lineNum == 0
        klineOfInstrumentID = {};
        klineOfInstrumentID{1} = char(arg.pKLine.ExchangeTime);
        klineOfInstrumentID{2} = [arg.pKLine.OpenPrice arg.pKLine.HighestPrice arg.pKLine.LowestPrice arg.pKLine.ClosePrice];
        KLineOfAllInstruments = setfield(KLineOfAllInstruments, InstrumentID, klineOfInstrumentID);
    else
        klineOfInstrumentID = getfield(KLineOfAllInstruments, InstrumentID);
        klineOfInstrumentID{1}(lineNum+1,:) = char(arg.pKLine.ExchangeTime);
        klineOfInstrumentID{2}(lineNum+1,:) = [arg.pKLine.OpenPrice arg.pKLine.HighestPrice arg.pKLine.LowestPrice arg.pKLine.ClosePrice];
        KLineOfAllInstruments = setfield(KLineOfAllInstruments, InstrumentID, klineOfInstrumentID);
    end
    
    global axes1;    
    axes(axes1);    
    candle(klineOfInstrumentID{2}(:,2), klineOfInstrumentID{2}(:,3), klineOfInstrumentID{2}(:,4), klineOfInstrumentID{2}(:,1));
end


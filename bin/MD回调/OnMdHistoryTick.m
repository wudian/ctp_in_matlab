function  OnMdHistoryTick( ~,  arg)
%
 %   str1 = sprintf('%s(%s)(%s)', char(arg.pTick.InstrumentID), char(arg.pTick.ExchangeTime), char(arg.pTick.LocalTime));
 %   disp(str1);
    
    Types;
    InstrumentID = strtrim(char(arg.pTick.InstrumentID));
    %{
    NPrice = setfield(NPrice, InstrumentID, arg.pTick.LastPrice);
    APrice = setfield(APrice, InstrumentID, arg.pTick.AskPrice1);
    AQuant = setfield(AQuant, InstrumentID, arg.pTick.AskVolume1);
    BPrice = setfield(BPrice, InstrumentID, arg.pTick.BidPrice1);
    BQuant = setfield(BQuant, InstrumentID, arg.pTick.BidVolume1);
    Volume = setfield(Volume, InstrumentID, arg.pTick.Volume);
    Chicang = setfield(Chicang, InstrumentID, arg.pTick.OpenInterest);
    %}
 
    disp(InstrumentID);

end


function OnRtnDepthMarketData(~, arg)
%订阅实时行情的响应，一个tick回调本方法一次
    Types;
	InstrumentID = strtrim(char(arg.pTick.InstrumentID));
    
    ExchangeTime = setfield(ExchangeTime, InstrumentID, arg.pTick.ExchangeTime);
    LocalTime = setfield(LocalTime, InstrumentID, arg.pTick.LocalTime);
    NPrice = setfield(NPrice, InstrumentID, arg.pTick.LastPrice);
    BPrice = setfield(BPrice, InstrumentID, arg.pTick.BidPrice1);
    BQuant = setfield(BQuant, InstrumentID, arg.pTick.BidVolume1);
    APrice = setfield(APrice, InstrumentID, arg.pTick.AskPrice1);
    AQuant = setfield(AQuant, InstrumentID, arg.pTick.AskVolume1);
    Volume = setfield(Volume, InstrumentID, arg.pTick.Volume);
    Turnover = setfield(Turnover, InstrumentID, arg.pTick.Turnover);
    OpenInterest = setfield(OpenInterest, InstrumentID, arg.pTick.OpenInterest);
    MaxP = setfield(MaxP, InstrumentID, arg.pTick.HighestPrice);
    MinP = setfield(MinP, InstrumentID, arg.pTick.LowestPrice);
    
    disp(NPrice);
end

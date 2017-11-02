function   OnRspQryDepthMarketData( ~, arg )
%单次行情响应
if arg.pRspInfo.ErrorID ~= 0
    str = sprintf('查询单个行情(%s)错误原因(%s)', InstrumentID, char(arg.pRspInfo.ErrorMsg));
    disp(str);
    return;
end

Types;
InstrumentID = char(arg.pDepthMarketData.InstrumentID);
%%初始化全局变量
%Tick
ExchangeTime = setfield(ExchangeTime, InstrumentID, '');
LocalTime = setfield(LocalTime, InstrumentID, '');
NPrice = setfield(NPrice, InstrumentID, NaN);
BPrice = setfield(BPrice, InstrumentID, NaN);
BQuant = setfield(BQuant, InstrumentID, NaN);
APrice = setfield(APrice, InstrumentID, NaN);
AQuant = setfield(AQuant, InstrumentID, NaN);
Volume = setfield(Volume, InstrumentID, NaN);
Turnover = setfield(Turnover, InstrumentID, NaN);
OpenInterest = setfield(OpenInterest, InstrumentID, NaN);
MaxP = setfield(MaxP, InstrumentID, NaN);
MinP = setfield(MinP, InstrumentID, NaN);
UpperLimitPrice = setfield(UpperLimitPrice, InstrumentID, arg.pDepthMarketData.UpperLimitPrice);
LowerLimitPrice = setfield(LowerLimitPrice, InstrumentID, arg.pDepthMarketData.LowerLimitPrice);
%KLine
ExchangeTime_KLine = setfield(ExchangeTime_KLine, InstrumentID, '');
OpenPrice = setfield(OpenPrice, InstrumentID, NaN);
HighestPrice = setfield(HighestPrice, InstrumentID, NaN);
LowestPrice = setfield(LowestPrice, InstrumentID, NaN);
ClosePrice = setfield(ClosePrice, InstrumentID, NaN);
Volume_KLine = setfield(Volume_KLine, InstrumentID, NaN);
OpenInterest_KLine = setfield(OpenInterest_KLine, InstrumentID, NaN);
% 可用报单 手数
AvailableOrderHands_BuyOpen = setfield(AvailableOrderHands_BuyOpen, InstrumentID, NaN);
AvailableOrderHands_BuyClose = setfield(AvailableOrderHands_BuyClose, InstrumentID, NaN);
AvailableOrderHands_BuyCloseToday = setfield(AvailableOrderHands_BuyCloseToday, InstrumentID, NaN);
AvailableOrderHands_SellOpen = setfield(AvailableOrderHands_SellOpen, InstrumentID, NaN);
AvailableOrderHands_SellClose = setfield(AvailableOrderHands_SellClose, InstrumentID, NaN);
AvailableOrderHands_SellCloseToday = setfield(AvailableOrderHands_SellCloseToday, InstrumentID, NaN);
% 成交单 手数
TradeHands_BuyOpen = setfield(TradeHands_BuyOpen, InstrumentID, NaN);
TradeHands_BuyClose = setfield(TradeHands_BuyClose, InstrumentID, NaN);
TradeHands_BuyCloseToday = setfield(TradeHands_BuyCloseToday, InstrumentID, NaN);
TradeHands_SellOpen = setfield(TradeHands_SellOpen, InstrumentID, NaN);
TradeHands_SellClose = setfield(TradeHands_SellClose, InstrumentID, NaN);
TradeHands_SellCloseToday = setfield(TradeHands_SellCloseToday, InstrumentID, NaN);
%持仓
TLPos = setfield(TLPos, InstrumentID, NaN);
ALPos = setfield(ALPos, InstrumentID, NaN);
OLPos = setfield(OLPos, InstrumentID, NaN);
NLPos = setfield(NLPos, InstrumentID, NaN);
ANLPos = setfield(ANLPos, InstrumentID, NaN);
LPosAvgPrice = setfield(LPosAvgPrice, InstrumentID, NaN);

TSPos = setfield(TSPos, InstrumentID, NaN);
ASPos = setfield(ASPos, InstrumentID, NaN);
OSPos = setfield(OSPos, InstrumentID, NaN);
NSPos = setfield(NSPos, InstrumentID, NaN);
ANSPos = setfield(ANSPos, InstrumentID, NaN);
SPosAvgPrice = setfield(SPosAvgPrice, InstrumentID, NaN);

end

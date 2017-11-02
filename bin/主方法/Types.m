%东航 Matlab量化组内部数据结构

%% 行情
global md;

% Tick   
%举例：要查询IF1409的最新价的方法: NPrice.IF1409,得到NaN表明无最新价
global ExchangeTime; %交易所时间戳(char)
global LocalTime; % 本地时间戳(char)
global NPrice; %最新价 
global BPrice; %买1价
global BQuant; %买1量
global APrice; %卖1价
global AQuant; %卖1量
global Volume; %成交量
global Turnover; %成交金额
global OpenInterest; %持仓量
global MaxP; %当日到达的最高价 
global MinP; %当日到达的最低价 
global UpperLimitPrice; %当天的涨停板
global LowerLimitPrice; %当天的跌停板

% KLine
%举例：要查询IF1409的3分钟K线的最高价：HighestPrice.IF1409.M3
global ExchangeTime_KLine;
global OpenPrice;
global HighestPrice;
global LowestPrice;
global ClosePrice;
global Volume_KLine;
global OpenInterest_KLine;

%% 交易
global td;

%资金账户
%假设投资者账户为00000015,则以下变量的key为'account00000015',
global FundAvailable; %可用资金
global CloseProfit; %平仓盈亏
global PositionProfit; %持仓盈亏
global Commission; %手续费
global FrozenCommission; %冻结手续费
global CurrMargin; %保证金总额
global FrozenMargin; %冻结的保证金
global Deposit; %入金金额
global Withdraw; %出金金额
global PreEquity; %上日权益
global CurrentEquity; %今日动态权益
global RiskRatio; %风险率

% 可用报单
global AvailableOrderPrice_BuyOpen; %买开单的均价
global AvailableOrderHands_BuyOpen; %买开单的手数
global AvailableOrderPrice_BuyClose;
global AvailableOrderHands_BuyClose;
global AvailableOrderPrice_BuyCloseToday;
global AvailableOrderHands_BuyCloseToday;
global AvailableOrderPrice_SellOpen;
global AvailableOrderHands_SellOpen;
global AvailableOrderPrice_SellClose;
global AvailableOrderHands_SellClose;
global AvailableOrderPrice_SellCloseToday;
global AvailableOrderHands_SellCloseToday;

% 所有报单
global AllOrderPrice_BuyOpen; %买开单的均价
global AllOrderHands_BuyOpen; %买开单的手数
global AllOrderPrice_BuyClose;
global AllOrderHands_BuyClose;
global AllOrderPrice_BuyCloseToday;
global AllOrderHands_BuyCloseToday;
global AllOrderPrice_SellOpen;
global AllOrderHands_SellOpen;
global AllOrderPrice_SellClose;
global AllOrderHands_SellClose;
global AllOrderPrice_SellCloseToday;
global AllOrderHands_SellCloseToday;

% 成交单
global TradePrice_BuyOpen;
global TradeHands_BuyOpen;
global TradePrice_BuyClose;
global TradeHands_BuyClose;
global TradePrice_BuyCloseToday;
global TradeHands_BuyCloseToday;
global TradePrice_SellOpen;
global TradeHands_SellOpen;
global TradePrice_SellClose;
global TradeHands_SellClose;
global TradePrice_SellCloseToday;
global TradeHands_SellCloseToday;

%持仓
global TLPos; %总多仓
global ALPos; %可用多仓
global OLPos; %昨开多仓
global NLPos; %今开多仓
global ANLPos; %今开可用多仓
global LPosAvgPrice; %多仓均价

global TSPos; %总空仓
global ASPos; %可用空仓
global OSPos; %昨开空仓
global NSPos; %今开空仓
global ANSPos; %今开可用空仓
global SPosAvgPrice; %空仓均价


%{
global AllInstruments; %{'', '', '', ...}
global KLineOfAllInstruments; %
%global longshort;
%}

%subfunctions mycallbacks.m of CTPCOM server.
%The call to str2func converts the input string to a function handle:
%2012-1-7 By chaos
function a = mycallbacks(str)
a = str2func(str);

function funOnInitFinished(varargin)
disp('Initialised!! ');
function funOnMDConnected(varargin)
disp('Market Data Connected!! ');
function funOnMDDisconnected(varargin)
disp('Market Data Disconnected!! ');
function funOnTradeConnected(varargin)
disp('Trade Connected!! ');
function funOnTradeDisconnected(varargin)
disp('Trade Disconnected!! ');

function funOnMarketData(varargin)
%OnMarketData = void OnMarketData(string 1InstrumentID, double 2BidPrice1, int32 3BidVolume1,
%double 4AskPrice1, int32 5AskVolume1, double 6OpenPrice, double 7HighestPrice, double 8LowestPrice,
%double 9LastPrice, int32 10OpenInterest, int32 11Volume, double 12UpperLimitPrice, double 13LowerLimitPrice,
%double 14PreSettlementPrice, double 15AveragePrice, string 16UpdateTime,
%int32 17UpdateMilliSecond)

%the real argument no. should plus 2

global  countInst instruments recInstrument; %recInstrument1 countInst1 ;
InstrumentID = varargin{3};
UpdateTime = strcat(num2str(varargin{18}),':',num2str(varargin{19}));
LastPrice = varargin{11};
Volume  = varargin{13};
AskPrice1 = varargin{6};
AskVolume1 = varargin{7};
BidPrice1 = varargin{4};
BidVolume1= num2cell(varargin{5});


if InstrumentID  == char(instruments(1,1))
    %if not state No.of instruments,need to put in front
    countInst = countInst + 1;
    
    recInstrument(countInst,2:9)=[UpdateTime,InstrumentID,LastPrice,Volume,...
        AskPrice1,AskVolume1,BidPrice1,BidVolume1];
    recInstrument(countInst,1)= {char(datestr(now,13))};
    % real time plotting
    plot(cell2mat(recInstrument(2:countInst,4)));
    

end

function funOnAccount(varargin)
%OnAccount = void OnAccount(double 3PreBalance, 4double Balance, 5double Available,
%6double Commission, 7double FrozenCommission, 8double Margin, 9double FrozenMargin,
%10double CloseProfit, 11double PositionProfit)
global accInfor;
PreBalance = varargin{3};
Balance = varargin{4};
Available = varargin{5};
Commission =varargin{6};
FrozenCommission = varargin{7};
Margin =varargin{8};
FrozenMargin=varargin{9};
CloseProfit=varargin{10};
PositionProfit = num2cell(varargin{11});
accInfor(2,1:9) = [PreBalance,Balance,Available,Commission,FrozenCommission,...
    Margin,FrozenMargin,CloseProfit,PositionProfit];

function funOnPosition(varargin)
%void OnPosition(3string InstrumentID, 4int32 IsLong, 5int32 Volume, 6double CloseProfit,
%7double PositionProfit, 8double AvgPositionPrice, 9double AvgOpenPrice,
%10int32 TotalClosable, 11int32 TodayClosable)

global postionInfor;

InstrumentID = varargin{3};
IsLong = varargin{4};
Volume = varargin{5};
CloseProfit =varargin{6};
PositionProfit = varargin{7};
AvgPositionPrice =varargin{8};
AvgOpenPrice=varargin{9};
TotalClosable=varargin{10};
TodayClosable = num2cell(varargin{11});
postionInfor(2,1:9) = [InstrumentID,IsLong,Volume,CloseProfit,...
    PositionProfit,AvgPositionPrice,AvgOpenPrice,TotalClosable,...
    TodayClosable];


function funOnOrder(varargin)
%OnOrder(3int32 OrderID, 4string InstrumentID, 5int32 IsBuy, 6int32 IsOpen, 7int32 Volume,
%8double Price, 9int32 TradedVolume, 10double AvgTradePrice, 11int32 OrderStatus,
%12string OrderSysID, 13string InsertTime, 14string ErrorMsg)
global orderInfor countOrder;

countOrder = countOrder + 1;
OrderID = varargin{3};
InstrumentID = {char(varargin{4})};
IsBuy = varargin{5};

if IsBuy ~= 0
    IsBuy = {'Buy'};
else
    IsBuy = {'Sell'};
end

IsOpen =varargin{6};

if IsOpen~=0
    IsOpen = {'Open'};
else
    IsOpen = {'Close'};
end

Volume = varargin{7};
Price = varargin{8};
TradedVolume=varargin{9};
AvgTradePrice=varargin{10};
OrderStatus = {char(varargin{11})};
OrderSysID = {char(varargin{12})};
InsertTime = {char(varargin{13})};
ErrorMsg = {char(varargin{14})};

orderInfor(countOrder,1:12) = [OrderID,InstrumentID,IsBuy,IsOpen,Volume,...
    Price,TradedVolume,AvgTradePrice,OrderStatus,OrderSysID,...
    InsertTime,ErrorMsg];

function funOnTrade(varargin)
%OnTrade = void OnTrade(3int32 OrderID, 4string InstrumentID, 5int32 IsBuy, 6int32 IsOpen,
%7int32 ThisTradeVolume, 8double ThisTradePrice, 9string TradeTime)

global tradeInfor countTrade;
countTrade = countTrade+1;
OrderID = varargin{3};
InstrumentID = varargin{4};
IsBuy = varargin{5};
IsOpen =varargin{6};
ThisTradeVolume = varargin{7};
ThisTradePrice =varargin{8};
TradeTime = {char(varargin{9})};

tradeInfor(countTrade,1:7) = [OrderID,InstrumentID,IsBuy,IsOpen,...
    ThisTradeVolume,ThisTradePrice,TradeTime];

disp(['OrderID: ',num2str(OrderID), ' is excuted']);
disp(['Instrument: ',num2str(InstrumentID),' Price: ',num2str(ThisTradePrice),...
    ' Time: ', char(TradeTime),' Vol :', num2str(ThisTradeVolume)]);

function funOnOrderCanceled(varargin)
%OnOrderCanceled = void OnOrderCanceled(int32 OrderID, int32 ErrorID, string ErrorMsg)
OrderID = varargin{3};
ErrorID = varargin{4};
ErrorMsg = varargin{5};
disp(['OrderID: ',num2str(OrderID), ' is canceled']);
disp(['ErrorID: ', num2str(ErrorID), 'ErrorMsg: ', char(ErrorMsg)]);

function funOnOrderFinished(varargin)
%OnOrderFinished = void OnOrderFinished(int32 OrderID)
disp(['OrderID  ', num2str(varargin{3}),' is finished']);
function funOnOrderActionFailed(varargin)
%void OnOrderActionFailed(int32 OrderID, int32 ErrorID)
disp(['OrderID:  ', num2str(varargin{3}),' is failed' ]);
disp(['ErrorID is ', char(varargin{4})]);



function  OnRspQryTradingAccount( ~ ,arg )
%返回资金账户

if arg.pRspInfo.ErrorID ~= 0
   str = sprintf('查询资金账户失败：%s', arg.pRspInfo.ErrorMsg); 
   disp(str);
   return;
end

Types;
AccountID = ['account' , char(arg.pTradingAccount.AccountID)]; %投资者账号

FundAvailable = setfield(FundAvailable, AccountID, arg.pTradingAccount.Available); %可用资金
CloseProfit = setfield(CloseProfit, AccountID, arg.pTradingAccount.CloseProfit); %平仓盈亏
PositionProfit = setfield(PositionProfit, AccountID, arg.pTradingAccount.PositionProfit); %持仓盈亏
Commission = setfield(Commission, AccountID, arg.pTradingAccount.Commission); %手续费
FrozenCommission = setfield(FrozenCommission, AccountID, arg.pTradingAccount.FrozenCommission); %冻结手续费
CurrMargin = setfield(CurrMargin, AccountID, arg.pTradingAccount.CurrMargin); %保证金总额
FrozenMargin = setfield(FrozenMargin, AccountID, arg.pTradingAccount.FrozenMargin); %冻结的保证金
Deposit = setfield(Deposit, AccountID, arg.pTradingAccount.Deposit); %入金金额
Withdraw = setfield(Withdraw, AccountID, arg.pTradingAccount.Withdraw); %出金金额
PreEquity = setfield(PreEquity, AccountID, arg.pTradingAccount.PreBalance); %上日权益

%静态权益=上日结算（上日权益）-出金金额+入金金额
sEquity = arg.pTradingAccount.PreBalance - arg.pTradingAccount.Withdraw + arg.pTradingAccount.Deposit;
%动态权益=静态权益+ 平仓盈亏+ 持仓盈亏- 手续费
dEquity = sEquity + arg.pTradingAccount.CloseProfit + arg.pTradingAccount.PositionProfit - arg.pTradingAccount.Commission;
CurrentEquity = setfield(CurrentEquity, AccountID, dEquity); %今日动态权益

%风险率 = 保证金 / 今日动态权益
RiskRatio = setfield(RiskRatio, AccountID, arg.pTradingAccount.CurrMargin / dEquity); %风险率

if arg.bIsLast == true
    disp('查资金账户完成')
end

str = sprintf('返回资金账户：投资者帐号(%s), 可用资金(%f)', char(arg.pTradingAccount.AccountID), arg.pTradingAccount.Available);
disp(str)

end


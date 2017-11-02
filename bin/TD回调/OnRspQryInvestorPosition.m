function OnRspQryInvestorPosition( ~, arg )
%查询投资者持仓响应

if arg.pRspInfo.ErrorID ~= 0
   disp(arg.pRspInfo.ErrorMsg);
   return;
end

Types;
InstrumentID = char(arg.pInvestorPosition.InstrumentID);
global VolumeMultiple; % 合约数量乘数
volumeMulti = getfield(VolumeMultiple, InstrumentID);

posi_direction = '多头';
if arg.pInvestorPosition.PosiDirection == QuantBox.CSharp2CTP.TThostFtdcPosiDirectionType.Long
    posi_direction = '多头';
    TLPos = setfield(TLPos, InstrumentID, arg.pInvestorPosition.Position); %总多仓
    ALPos = setfield(ALPos, InstrumentID, arg.pInvestorPosition.Position - arg.pInvestorPosition.LongFrozen); %可用多仓=总多仓-多头冻结
    OLPos = setfield(OLPos, InstrumentID, arg.pInvestorPosition.YdPosition); %昨开多仓
    NLPos = setfield(NLPos, InstrumentID, arg.pInvestorPosition.TodayPosition); %今开多仓   
    LPosAvgPrice = setfield(LPosAvgPrice, InstrumentID, arg.pInvestorPosition.PositionCost / volumeMulti); %多仓均价 
else
    posi_direction = '空头';
    TSPos = setfield(TSPos, InstrumentID, arg.pInvestorPosition.Position); %总空仓
    ASPos = setfield(ASPos, InstrumentID, arg.pInvestorPosition.Position - arg.pInvestorPosition.ShortFrozen); %可用空仓=总空仓-空头冻结
    OSPos = setfield(OSPos, InstrumentID, arg.pInvestorPosition.YdPosition); %昨开空仓
    NSPos = setfield(NSPos, InstrumentID, arg.pInvestorPosition.TodayPosition); %今开空仓
    SPosAvgPrice = setfield(SPosAvgPrice, InstrumentID, arg.pInvestorPosition.PositionCost / volumeMulti); %空仓均价
end

str = sprintf('查询投资者持仓响应: 合约代码(%s),投资者代码(%s),持仓多空方向(%s),上日持仓(%d),今日持仓(%d),开仓量(%d)，平仓量(%d)', char(InstrumentID), char(arg.pInvestorPosition.InvestorID), posi_direction, arg.pInvestorPosition.YdPosition, arg.pInvestorPosition.Position, arg.pInvestorPosition.OpenVolume, arg.pInvestorPosition.CloseVolume);
disp(str)
if arg.bIsLast == true
    disp('查询持仓完成'); 
end
end



%{
/// <summary>
    /// 投资者持仓
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct CThostFtdcInvestorPositionField
    {
        /// <summary>
        /// 合约代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 31)]
        public string InstrumentID;
        /// <summary>
        /// 经纪公司代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string BrokerID;
        /// <summary>
        /// 投资者代码
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 13)]
        public string InvestorID;
        /// <summary>
        /// 持仓多空方向
        /// </summary>
        public TThostFtdcPosiDirectionType PosiDirection;
        /// <summary>
        /// 投机套保标志
        /// </summary>
        public TThostFtdcHedgeFlagType HedgeFlag;
        /// <summary>
        /// 持仓日期
        /// </summary>
        public TThostFtdcPositionDateType PositionDate;
        /// <summary>
        /// 上日持仓
        /// </summary>
        public int YdPosition;
        /// <summary>
        /// 今日持仓
        /// </summary>
        public int Position;
        /// <summary>
        /// 多头冻结
        /// </summary>
        public int LongFrozen;
        /// <summary>
        /// 空头冻结
        /// </summary>
        public int ShortFrozen;
        /// <summary>
        /// 开仓冻结金额
        /// </summary>
        public double LongFrozenAmount;
        /// <summary>
        /// 开仓冻结金额
        /// </summary>
        public double ShortFrozenAmount;
        /// <summary>
        /// 开仓量
        /// </summary>
        public int OpenVolume;
        /// <summary>
        /// 平仓量
        /// </summary>
        public int CloseVolume;
        /// <summary>
        /// 开仓金额
        /// </summary>
        public double OpenAmount;
        /// <summary>
        /// 平仓金额
        /// </summary>
        public double CloseAmount;
        /// <summary>
        /// 持仓成本
        /// </summary>
        public double PositionCost;
        /// <summary>
        /// 上次占用的保证金
        /// </summary>
        public double PreMargin;
        /// <summary>
        /// 占用的保证金
        /// </summary>
        public double UseMargin;
        /// <summary>
        /// 冻结的保证金
        /// </summary>
        public double FrozenMargin;
        /// <summary>
        /// 冻结的资金
        /// </summary>
        public double FrozenCash;
        /// <summary>
        /// 冻结的手续费
        /// </summary>
        public double FrozenCommission;
        /// <summary>
        /// 资金差额
        /// </summary>
        public double CashIn;
        /// <summary>
        /// 手续费
        /// </summary>
        public double Commission;
        /// <summary>
        /// 平仓盈亏
        /// </summary>
        public double CloseProfit;
        /// <summary>
        /// 持仓盈亏
        /// </summary>
        public double PositionProfit;
        /// <summary>
        /// 上次结算价
        /// </summary>
        public double PreSettlementPrice;
        /// <summary>
        /// 本次结算价
        /// </summary>
        public double SettlementPrice;
        /// <summary>
        /// 交易日
        /// </summary>
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 9)]
        public string TradingDay;
        /// <summary>
        /// 结算编号
        /// </summary>
        public int SettlementID;
        /// <summary>
        /// 开仓成本
        /// </summary>
        public double OpenCost;
        /// <summary>
        /// 交易所保证金
        /// </summary>
        public double ExchangeMargin;
        /// <summary>
        /// 组合成交形成的持仓
        /// </summary>
        public int CombPosition;
        /// <summary>
        /// 组合多头冻结
        /// </summary>
        public int CombLongFrozen;
        /// <summary>
        /// 组合空头冻结
        /// </summary>
        public int CombShortFrozen;
        /// <summary>
        /// 逐日盯市平仓盈亏
        /// </summary>
        public double CloseProfitByDate;
        /// <summary>
        /// 逐笔对冲平仓盈亏
        /// </summary>
        public double CloseProfitByTrade;
        /// <summary>
        /// 今日持仓
        /// </summary>
        public int TodayPosition;
        /// <summary>
        /// 保证金率
        /// </summary>
        public double MarginRateByMoney;
        /// <summary>
        /// 保证金率(按手数)
        /// </summary>
        public double MarginRateByVolume;
        /// <summary>
        /// 执行冻结
        /// </summary>
        public int StrikeFrozen;
        /// <summary>
        /// 执行冻结金额
        /// </summary>
        public double StrikeFrozenAmount;
        /// <summary>
        /// 放弃执行冻结
        /// </summary>
        public int AbandonFrozen;
        /// <summary>
        /// 期权市值
        /// </summary>
        public double OptionValue;
    }
%}
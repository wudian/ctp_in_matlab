using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuantBoxCSharp
{
    public delegate void OnConnectHandler(object sender, OnConnectArgs e);
    public delegate void OnDisconnectHandler(object sender, OnDisconnectArgs e);
    public delegate void OnRspErrorHandler(object sender, OnRspErrorArgs e);

    public delegate void OnTickHandler(object sender, OnTickArgs e);
    public delegate void OnKLineHandler(object sender, OnKLineArgs e);

    public delegate void OnRtnDepthMarketDataHandler(object sender, OnTickArgs e);

    public delegate void OnErrRtnOrderActionHandler(object sender, OnErrRtnOrderActionArgs e);
    public delegate void OnErrRtnOrderInsertHandler(object sender, OnErrRtnOrderInsertArgs e);
    public delegate void OnRspOrderActionHandler(object sender, OnRspOrderActionArgs e);
    public delegate void OnRspOrderInsertHandler(object sender, OnRspOrderInsertArgs e);
    public delegate void OnRspQryDepthMarketDataHandler(object sender, OnRspQryDepthMarketDataArgs e);
    public delegate void OnRspQryInstrumentHandler(object sender, OnRspQryInstrumentArgs e);
    public delegate void OnRspQryInstrumentCommissionRateHandler(object sender, OnRspQryInstrumentCommissionRateArgs e);
    public delegate void OnRspQryInstrumentMarginRateHandler(object sender, OnRspQryInstrumentMarginRateArgs e);
    public delegate void OnRspQryInvestorPositionHandler(object sender, OnRspQryInvestorPositionArgs e);
    public delegate void OnRspQryInvestorPositionDetailHandler(object sender, OnRspQryInvestorPositionDetailArgs e);
    public delegate void OnRspQrySettlementInfoHandler(object sender, OnRspQrySettlementInfoArgs e);//查结算
    public delegate void OnRspQryOrderHandler(object sender, OnRspQryOrderArgs e);//查委托
    public delegate void OnRspQryTradeHandler(object sender, OnRspQryTradeArgs e);//查成交
    public delegate void OnRspQryTradingAccountHandler(object sender, OnRspQryTradingAccountArgs e);
    public delegate void OnRtnInstrumentStatusHandler(object sender, OnRtnInstrumentStatusArgs e);
    public delegate void OnRtnOrderHandler(object sender, OnRtnOrderArgs e);
    public delegate void OnRtnTradeHandler(object sender, OnRtnTradeArgs e);
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuantBoxCSharp
{
    //通用
    public class OnConnectArgs : EventArgs
    {
        public readonly ConnectionStatus result;
        public OnConnectArgs(ConnectionStatus result)
        {
            this.result = result;
        }
    }

    public class OnDisconnectArgs : EventArgs
    {
        
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly ConnectionStatus step;
        public OnDisconnectArgs(ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {
            
            this.pRspInfo = pRspInfo;
            this.step = step;
        }
    }

    public class OnRspErrorArgs : EventArgs
    {
        
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspErrorArgs(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    // 历史行情
    public class OnTickArgs : EventArgs
    {
        public readonly CTick pTick;
        public OnTickArgs(ref CTick pTick)
        {
            this.pTick = pTick;
        }
    }

    public class OnKLineArgs : EventArgs
    {
        public readonly CKLine pKLine;
        public OnKLineArgs(ref CKLine pKLine)
        {
            this.pKLine = pKLine;
        }
    }

    //行情
    public class OnRtnDepthMarketDataArgs : EventArgs
    {
        public readonly CThostFtdcDepthMarketDataField pDepthMarketData;
        public OnRtnDepthMarketDataArgs(ref CThostFtdcDepthMarketDataField pDepthMarketData)
        {
            this.pDepthMarketData = pDepthMarketData;
        }
    }

    //交易
    public class OnErrRtnOrderActionArgs : EventArgs
    {
        
        public readonly CThostFtdcOrderActionField pOrderAction;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public OnErrRtnOrderActionArgs(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo)
        {
            
            this.pOrderAction = pOrderAction;
            this.pRspInfo = pRspInfo;
        }
    }

    public class OnErrRtnOrderInsertArgs : EventArgs
    {
        
        public readonly CThostFtdcInputOrderField pInputOrder;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public OnErrRtnOrderInsertArgs(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo)
        {
            
            this.pInputOrder = pInputOrder;
            this.pRspInfo = pRspInfo;
        }
    }

    public class OnRspOrderActionArgs : EventArgs
    {
        
        public readonly CThostFtdcInputOrderActionField pInputOrderAction;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspOrderActionArgs(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInputOrderAction = pInputOrderAction;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspOrderInsertArgs : EventArgs
    {
        
        public readonly CThostFtdcInputOrderField pInputOrder;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspOrderInsertArgs(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInputOrder = pInputOrder;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryDepthMarketDataArgs : EventArgs
    {
        
        public readonly CThostFtdcDepthMarketDataField pDepthMarketData;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryDepthMarketDataArgs(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pDepthMarketData = pDepthMarketData;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryInstrumentArgs : EventArgs
    {
        
        public readonly CThostFtdcInstrumentField pInstrument;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryInstrumentArgs(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInstrument = pInstrument;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryInstrumentCommissionRateArgs : EventArgs
    {
        
        public readonly CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryInstrumentCommissionRateArgs(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInstrumentCommissionRate = pInstrumentCommissionRate;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryInstrumentMarginRateArgs : EventArgs
    {
        
        public readonly CThostFtdcInstrumentMarginRateField pInstrumentMarginRate;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryInstrumentMarginRateArgs(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInstrumentMarginRate = pInstrumentMarginRate;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryInvestorPositionArgs : EventArgs
    {
        
        public readonly CThostFtdcInvestorPositionField pInvestorPosition;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryInvestorPositionArgs(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInvestorPosition = pInvestorPosition;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryInvestorPositionDetailArgs : EventArgs
    {
        
        public readonly CThostFtdcInvestorPositionDetailField pInvestorPositionDetail;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryInvestorPositionDetailArgs(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pInvestorPositionDetail = pInvestorPositionDetail;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQrySettlementInfoArgs : EventArgs
    {
        
        public readonly CThostFtdcSettlementInfoField pSettlementInfo;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQrySettlementInfoArgs(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pSettlementInfo = pSettlementInfo;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryOrderArgs : EventArgs
    {
        
        public readonly CThostFtdcOrderField pOrder;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryOrderArgs(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pOrder = pOrder;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryTradeArgs : EventArgs
    {
        
        public readonly CThostFtdcTradeField pTrade;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryTradeArgs(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pTrade = pTrade;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRspQryTradingAccountArgs : EventArgs
    {
        
        public readonly CThostFtdcTradingAccountField pTradingAccount;
        public readonly CThostFtdcRspInfoField pRspInfo;
        public readonly int nRequestID;
        public readonly bool bIsLast;
        public OnRspQryTradingAccountArgs(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            
            this.pTradingAccount = pTradingAccount;
            this.pRspInfo = pRspInfo;
            this.nRequestID = nRequestID;
            this.bIsLast = bIsLast;
        }
    }

    public class OnRtnOrderArgs : EventArgs
    {
        
        public readonly CThostFtdcOrderField pOrder;
        public OnRtnOrderArgs(ref CThostFtdcOrderField pOrder)
        {
            
            this.pOrder = pOrder;
        }
    }

    public class OnRtnTradeArgs : EventArgs
    {
        
        public readonly CThostFtdcTradeField pTrade;
        public OnRtnTradeArgs(ref CThostFtdcTradeField pTrade)
        {
            
            this.pTrade = pTrade;
        }
    }

    public class OnRtnInstrumentStatusArgs : EventArgs
    {
        
        public readonly CThostFtdcInstrumentStatusField pInstrumentStatus;
        public OnRtnInstrumentStatusArgs(ref CThostFtdcInstrumentStatusField pInstrumentStatus)
        {
            
            this.pInstrumentStatus = pInstrumentStatus;
        }
    }
}

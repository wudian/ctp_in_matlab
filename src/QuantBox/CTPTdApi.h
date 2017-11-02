#ifndef _CTP_TD_API_
#define _CTP_TD_API_


#include <time.h>
#include <thread>
#include <set>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <mutex>
#include <memory>
#include "CTP/ThostFtdcTraderApi.h"
#include "CTPCommonApi.h"
#include "defines.h"
#include "Types.h"

enum wdOrderType;
enum E_CTPReqType;
class CCTPReqMsgItem;
class CMyThreads;
struct wdLimitPrice;
struct wdOrderKey;
struct wdOrder;
struct wdPositionKey;
struct wdPosition;

/*! 交易接口 */
class CCTPTdApi : public CThostFtdcTraderSpi, CCTPCommonApi
{
public:
	static CCTPTdApi *instance();

	void Connect();
	void Disconnect();

	/*!	\brief 发单-限价
		\param Instrument 合约名
		\param Price 价格
		\param Volume 数量
		\param Direction 买卖方向
		\param OffsetFlag 开平标志
	*/
	void SendLimitOrder(const char *Instrument, double Price, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag);
	/*!	\brief 报单-市价
		\param Instrument 合约名
		\param Volume 数量
		\param Direction 买卖方向
		\param OffsetFlag 开平标志
	*/
	void TD_SendMarketOrder(const char *Instrument, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag);
	/*!	\brief 报单-触发单
		\param Instrument 合约名
		\param Price 价格
		\param Volume 数量
		\param Direction 买卖方向
		\param OffsetFlag 开平标志
		\param ContingentCondition 触发条件
		\param StopPrice 止损价
	*/
	void TD_SendContingentOrder(const char *Instrument, double Price, int Volume, wdDirectionType Direction, wdOffsetFlagType OffsetFlag, wdContingentConditionType ContingentCondition, double StopPrice);
	
	/*!	\brief 撤单
		\param Instrument 合约名
		\param Direction 买卖方向
		\param OffsetFlag 开平标志
	*/
	void CancelOrder(const char *Instrument, wdDirectionType Direction = E_Direction_Default, wdOffsetFlagType OffsetFlag = E_OffsetFlag_Default);
	void CancelOrder(wdOrder &);
	

	///查询结算单
	void ReqQrySettlementInfo(const char *szTradingDay);
	///请求查询报单
	void ReqQryOrder(const char *InstrumentID = nullptr);
	///请求查询成交
	void ReqQryTrade(const char *InstrumentID = nullptr);
	///查持仓
	void ReqQryInvestorPosition(const char *szInstrumentId = nullptr);
	//查持仓明细
	void ReqQryInvestorPositionDetail(const char *szInstrumentId = nullptr);

	///查资金
	void ReqQryTradingAccount();
	///查合约
	void ReqQryInstrument(const char *szInstrumentId = nullptr);	
	///查手续费 按合约查询，以品种响应
	void ReqQryInstrumentCommissionRate(const char *szInstrumentId = nullptr);
	///查保证金 只能按合约查询
	void ReqQryInstrumentMarginRate(const char *szInstrumentId = nullptr, TThostFtdcHedgeFlagType HedgeFlag = THOST_FTDC_HF_Speculation);

	std::string GetAllInstruments();
	int GetVolumeMultiple(const std::string &inst);

private:
	CCTPTdApi(void);
	virtual ~CCTPTdApi(void);

	void _RunInThread(); //数据包发送线程
	void InputReqQueue(const std::shared_ptr<CCTPReqMsgItem> &);

	void ReqAuthenticate();
	///用户登录请求
	void ReqUserLogin();

	///查询当天客户结算单确认情况，无记录返回表示当天尚未确认结算单
	void ReqQrySettlementInfoConfirm();
	///确认结算单
	void ReqSettlementInfoConfirm();

	//连接
	virtual void OnFrontConnected();
	virtual void OnFrontDisconnected(int nReason);
	void OnFrontDisconnected(wdConnectionStatus status, const char *szReason);

	//认证
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//Thost收到报单指令，如果没有通过参数检验，拒绝接受此报单
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//交易所收到报单后认为报单错误
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

	//撤单
	//Thost收到撤单指令，如果没有通过参数检验，拒绝接受撤单指令
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//交易所认为报单错误
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);	
	
	//委托
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//成交
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

	//报价录入
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote);
	
	//报价撤单
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

	//仓位
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	//资金
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//合约
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//保证金 只能按合约查询
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//手续费 按合约查询，以品种响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//通知交易所状态变化
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);


	///查询行情。获取全部合约的列表，以及全部合约的涨跌停价
	void ReqQryDepthMarketData();
	///行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//其它
	virtual bool Checking();
	void DoSthOnBeginning(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID = UNIQUE_REQUEST_ID, bool bIsLast = true);
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	bool _IsMyOrder(TThostFtdcOrderRefType OrderRef);
	void _ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, wdOrderType);

	/*! \brief 报单操作:挂起、激活、修改、撤单。目前只支持撤单 */
	//int _ReqOrderAction(CThostFtdcInputOrderActionField *orderAction);
	
	int ReqQuoteInsert(
		int QuoteRef,
		const char *szInstrumentId,
		TThostFtdcPriceType	AskPrice,
		TThostFtdcPriceType	BidPrice,
		TThostFtdcVolumeType AskVolume,
		TThostFtdcVolumeType BidVolume,
		TThostFtdcOffsetFlagType AskOffsetFlag,
		TThostFtdcOffsetFlagType BidOffsetFlag,
		TThostFtdcHedgeFlagType	AskHedgeFlag,
		TThostFtdcHedgeFlagType	BidHedgeFlag
		);
	int ReqQuoteAction(CThostFtdcQuoteField *pQuote);

private:
	CThostFtdcTraderApi								*m_pApi;				//交易API	

	std::atomic<unsigned int>						m_nMaxOrderRef;			//报单引用，用于区分报单，保持自增

	int												m_nSleep;
	std::mutex										m_reqMutex;
	std::condition_variable							m_reqConditionVariable;
	std::queue<std::shared_ptr<CCTPReqMsgItem> >	m_reqQueue;
	std::map<E_CTPReqType, bool>					m_mapUniqueReq;			// 规避重复的请求
	std::shared_ptr<CMyThreads>						m_pReqThreads;

	// 交易数据============
	std::map<std::string, std::string>				m_mapSettlementInfo;	// 交易日->结算信息
	
	std::map<wdOrderKey, wdOrder>					m_mapOrders;
	std::map<wdPositionKey, wdPosition>				m_mapPositions;

	std::mutex										m_mutexInstruments;
	std::map<std::string, wdInstrument>				m_Instruments;			// 合约映射表,key为合约
	std::condition_variable							m_cv_Instruments;
};

#endif
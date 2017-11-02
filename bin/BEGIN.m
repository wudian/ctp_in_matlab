%% 导入C#库，请按自己目录进行调整
p = pwd;cd(p);
NET.addAssembly(fullfile(cd,'QuantBoxCSharp.dll'));
import QuantBoxCSharp.*;

%% 添加m文件搜索路径
addpath(cd) 
addpath(fullfile(cd,'\MD回调')) 
addpath(fullfile(cd, '\TD回调')) 
addpath(fullfile(cd, '\策略'))   
addpath(fullfile(cd, '\主方法'))  
addpath(fullfile(cd, '\主方法\保留方法'))  
addpath(fullfile(cd, '\UI'))  

%% 行情
global md;
md =  MdApiWrapper();
addlistener(md,'OnConnect',@OnMdConnect);
addlistener(md,'OnDisconnect',@OnMdDisconnect);
addlistener(md,'OnRspError',@OnRspError);
addlistener(md,'OnRtnDepthMarketData_Tick',@OnRtnDepthMarketData);
addlistener(md,'OnHistoryTick',@OnMdHistoryTick);
addlistener(md,'OnHistoryKLine',@OnMdHistoryKLine);

ConnectMD();


%% 交易
global td;
td = TraderApiWrapper();
addlistener(td,'OnConnect',@OnTdConnect);
addlistener(td,'OnDisconnect',@OnTdDisconnect);
addlistener(td,'OnErrRtnOrderAction',@OnErrRtnOrderAction);
addlistener(td,'OnErrRtnOrderInsert',@OnErrRtnOrderInsert);
addlistener(td,'OnRspError',@OnRspError);
addlistener(td,'OnRspOrderAction',@OnRspOrderAction);
addlistener(td,'OnRspOrderInsert',@OnRspOrderInsert);
addlistener(td,'OnRspQryDepthMarketData',@OnRspQryDepthMarketData);
addlistener(td,'OnRspQryInstrument',@OnRspQryInstrument);
addlistener(td,'OnRspQryInstrumentCommissionRate',@OnRspQryInstrumentCommissionRate);
addlistener(td,'OnRspQryInstrumentMarginRate',@OnRspQryInstrumentMarginRate);
addlistener(td,'OnRspQryInvestorPosition',@OnRspQryInvestorPosition);
addlistener(td,'OnRspQryInvestorPositionDetail',@OnRspQryInvestorPositionDetail);
addlistener(td,'OnRspQrySettlementInfo',@OnRspQrySettlementInfo);
addlistener(td,'OnRspQryOrder',@OnRspQryOrder);
addlistener(td,'OnRspQryTrade',@OnRspQryTrade);
addlistener(td,'OnRspQryTradingAccount',@OnRspQryTradingAccount);
addlistener(td,'OnRtnInstrumentStatus',@OnRtnInstrumentStatus);
addlistener(td,'OnRtnOrder',@OnRtnOrder);
addlistener(td,'OnRtnTrade',@OnRtnTrade);

ConnectTD();

%{
global t;
t = timer('Period', 2,  'ExecutionMode','fixedRate','TimerFcn',@Wudian_Strategy);
start( t );
%}

Types;
if ~isfield(NPrice, 'IF1408') || ~isfield(TLPos, 'IF1408')
    return;
end

if NPrice.IF1408 < 2330 %IF1408的最新价低于2330
    trade_list = QryTrade('IF1408','buy','Open');
    if strcmpi(trade_list, '') %IF1408没有买开的成交单
        availabe_orders = QryOrder('Available', 'IF1408','buy','');
        if strcmpi(availabe_orders, '') %没有可用单
            SendLimitOrder('IF1408', 2330, 'buy','open',1);
        else %有可用单
            CancelOrder(availabe_orders);
        end
    end
end

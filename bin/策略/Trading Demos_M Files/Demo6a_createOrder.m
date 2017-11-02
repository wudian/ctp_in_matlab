% On exchange state update, display info on the screen.
x.Gate.registerevent({'OnExchangeStateUpdate',@(varargin)ttorderserverstatus(varargin{:},sExchange)})
% Create OrderSet
x.createOrderSet;
% Set order: set properties and detail level of order status events
% Set a notification to display when order is rejected.
x.OrderSet(1).EnableOrderRejectData = 1;
x.OrderSet(1).EnableOrderUpdateData = 1;
x.OrderSet(1).OrderStatusNotifyMode = 'ORD_NOTIFY_NORMAL';
% Set the maximum number of shares you can trade. You can do more complex 
%orders in X_TRADER, but we are only going to show some basic examples here: 
%how to set limit orders and market orders.
x.OrderSet(1).Set('NetLimits',false)
%shows the events associated with the OrderSet object
x.OrderSet.registerevent({'OnOrderFilled',@(varargin)ttorderevent(varargin{:},x)})
x.OrderSet.registerevent({'OnOrderRejected',@(varargin)ttorderevent(varargin{:},x)})
x.OrderSet.registerevent({'OnOrderSubmitted',@(varargin)ttorderevent(varargin{:},x)})
x.OrderSet.registerevent({'OnOrderDeleted',@(varargin)ttorderevent(varargin{:},x)})
% Enable send orders (we first have to open the connection)
x.OrderSet.Open(1);
% Build order profile with existing instrument 
orderProfile = x.createOrderProfile;
orderProfile.Instrument = x.Instrument(1);
% Set customer default property (we are using a default customer profile)
orderProfile.Customer = '<Default>';
% Set up order profile as a market order to buy 1 contracts
orderProfile.Set('BuySell','Buy');
orderProfile.Set('Qty','1');
%Limit order, set the ordertype and limit order price
%
orderProfile.Set('OrderType','L');
orderProfile.Set('Limit$','15350');
% If we did all this, this just creates an order definition, but does not
% send the order to the market.

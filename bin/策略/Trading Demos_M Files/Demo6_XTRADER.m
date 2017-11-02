%% X_Trader Order Submission Example
% This example shows how to create an order and submit it.    Note that X_Trader is a 32-bit application and will only
% work with 32-bit Windows installations of MATLAB.
%
%  Copyright 2012 The MathWorks, Inc.
%% Start or connect to XTrader
x = xtrdr;

%% Create instruments

% NK225 and NK300 Jun 2013 expiry futures
x.createInstrument(...
    'Exchange','OSE-B','Product','NK225','ProdType','Future','Contract','Jun13');

% x.createInstrument(...
%     'Exchange','SGX-C','Product','IN','ProdType','Future','Contract','Jun13');

% Get instrument data.
instrData = getData(x, {'Exchange', 'Last', 'Bid', 'BidQty', 'Ask', 'AskQty'})

% Create event notifier (to invoke a callback every time an event occurrs, 
% e.g. display the price every time the price get changed
x.createNotifier

% Define events
x.InstrNotify.registerevent({'OnNotifyFound',@(varargin)ttinstrumentfound(varargin{:})})
x.InstrNotify.registerevent({'OnNotifyNotFound',@(varargin)ttinstrumentnotfound(varargin{:})})
x.InstrNotify.registerevent({'OnNotifyUpdate',@(varargin)ttinstrumentupdate(varargin{:},x)})

% Attach instruments to a notifier
x.InstrNotify.AttachInstrument(x.Instrument(1))

% Start monitoring events
x.Instrument(1).Open;

%% Stop the notification of events
x.InstrNotify.DetachInstrument(x.Instrument(1))

%% Register event handler for order server (another type of event handler)
sExchange = x.Instrument(1).Exchange;
Demo6a_createOrder

%% Send the order to the market

%Check order server status before submitting order, added counter so that
%demo never gets stuck
nCounter = 1;
while ~exist('bServerUp','var') && nCounter < 20
  %bServerUp is created by ttorderserverstatus
  pause(1)
  nCounter = nCounter + 1;
end

% If the order server is up,we submit the order using the following command
if exist('bServerUp','var') && bServerUp
  %Submit the order
  submittedQuantity = x.OrderSet(1).SendOrder(orderProfile);
  disp(['Quantity Sent: '  num2str(submittedQuantity)])
else
  disp('Order server is down.  Unable to submit order.')
end

% Now check the command line and go to X_TRADER (current working orders). 
% We can see in command line is submitted.

%%
%To delete an order
OrderObj = orderProfile.GetLastOrder;
if ~isempty(OrderObj)
  if ~OrderObj.IsNull
    OrderObj.DeleteOrder;
  end
end

%
disp('Shutting down communications to X_Trader.')
close(x)

% This is the process for trading with MATLAB through X_TRADER
% If the market is busy and MATLAB gets lot of submissions, orders will not
% be cancelled, but put in the queue for .NET boundary for the COM object.
% However, the latencies can be occur. You can try to use parallel
% computing to speed things up.
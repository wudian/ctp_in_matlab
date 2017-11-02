function sendOrder(signal, signalDate, signalTime, signalPrice)
%   SENDORDER produces a message on a Microsoft Messaging Queue
%

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.

% Assumes a binary state, either holding a security or not
persistent tradeState;
if ~exist('tradeState', 'var') || isempty(tradeState)
    tradeState = 'none';
end

% Get a handle to the queue
q = createMSMQ();

% Generate a message with information about buy/sell depending on the
% input signal and the current state of holding.
if signal
    switch tradeState
        case 'none'
            % Signal is buy and currently not holding a security,
            % place a buy order
            q.Send([signalDate ', ' signalTime ', ' 'buy' ', ' num2str(signalPrice)]);
            tradeState = 'long';
        case 'short'
            % Signal is buy and currently shorting a security,
            % place a buy order
            q.Send([signalDate ', ' signalTime ', ' 'buy' ', ' num2str(signalPrice)]);
            tradeState = 'long';
    end
else
    switch tradeState
        case 'none'
            % Signal is sell and currently not holding a security,
            % place a sell order
            q.Send([signalDate ', ' signalTime ', ' 'sell' ', ' num2str(signalPrice)]);
            tradeState = 'short';        
        case 'long'
            % Signal is sell and currently long a security,
            % place a sell order
            q.Send([signalDate ', ' signalTime ', ' 'sell' ', ' num2str(signalPrice)]);
            tradeState = 'short';
        
    end
end
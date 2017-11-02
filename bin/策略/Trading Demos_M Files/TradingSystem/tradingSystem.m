function tradingSystem(varargin)

persistent securityData;

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.

% Load in values from our backtesting
productionParams = load('productionParams.mat');

% Get the data from Reuters and parse it to create a series on which to use
% our signal generation algorithms.

tickData = varargin{1};
if isfield(tickData, 'HIGH_1') && isfield(tickData, 'LOW_1') && isfield(tickData, 'HST_CLOSE')
    newData = [tickData.HIGH_1 tickData.LOW_1 tickData.HST_CLOSE];  
    if ~exist('securityData','var') || isempty(securityData)
        securityData = newData;
    else
        % Window the data so that we only have 400 elements at a time
        if length(securityData) >= productionParams.M + 25
            securityData = [securityData(2:end,:); newData];
        else
            securityData = [securityData; newData];
        end
    end
    
    % "Burn in" data up to the value for our lag so that we can accurately
    % use our algorithms.
    if length(securityData) > productionParams.M
        
        % Pass the data to our algorithm and generate a signal
        out = generateTradeSignal(securityData);
        
        % Process the signal using a Microsoft Messaging Queue
        sendOrder(out, tickData.TRADE_DATE, tickData.TRDTIM_1, tickData.HST_CLOSE)      
        
    end
end
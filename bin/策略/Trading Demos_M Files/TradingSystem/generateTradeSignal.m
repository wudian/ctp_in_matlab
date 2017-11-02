function out = generateTradeSignal(signalData)
% GENERATETRADESIGNAL produces a buy/sell signal depending using parameters
% defined through backtesting.

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.

% Load parameters from backtesting
productionParams = load('productionParams.mat');

% Use trading algorithms with the new data to generate signals
sma = leadlag(signalData(:,end),productionParams.N,productionParams.M,productionParams.annualScaling,productionParams.cost);
srs = rsi(signalData(:,end),[productionParams.P productionParams.Q],productionParams.thresh,productionParams.annualScaling,productionParams.cost);
swr = wpr(signalData,productionParams.param,productionParams.annualScaling,productionParams.cost);
signals = [sma(end) srs(end) swr(end)];

% Use the bitstring with our signal to determine the buy/sell signal from
% this data
out = tradeSignal(productionParams.best,signals);

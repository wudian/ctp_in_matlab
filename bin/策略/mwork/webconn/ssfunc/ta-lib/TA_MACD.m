function [outMACD, outMACDSignal, outMACDHist] = TA_MACD ( inReal, FastPeriod, SlowPeriod, SignalPeriod )
%
% Moving Average Convergence/Divergence
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInFastPeriod: (Range from 2 to 100000) Description: Number of period for the fast MA
%	optInSlowPeriod: (Range from 2 to 100000) Description: Number of period for the slow MA
%	optInSignalPeriod: (Range from 1 to 100000) Description: Smoothing for the signal line (nb of period)
%
% Output
%	outMACD
%	outMACDSignal
%	outMACDHist
%
% See also: ta-lib

function [outMACD, outMACDSignal, outMACDHist] = TA_MACDFIX ( inReal, SignalPeriod )
%
% Moving Average Convergence/Divergence Fix 12/26
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInSignalPeriod: (Range from 1 to 100000) Description: Smoothing for the signal line (nb of period)
%
% Output
%	outMACD
%	outMACDSignal
%	outMACDHist
%
% See also: ta-lib

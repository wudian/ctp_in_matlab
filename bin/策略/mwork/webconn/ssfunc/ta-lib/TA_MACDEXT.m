function [outMACD, outMACDSignal, outMACDHist] = TA_MACDEXT ( inReal, FastPeriod, FastMA, SlowPeriod, SlowMA, SignalPeriod, SignalMA )
%
% MACD with controllable MA type
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInFastPeriod: (Range from 2 to 100000) Description: Number of period for the fast MA
%	optInFastMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for fast MA
%	optInSlowPeriod: (Range from 2 to 100000) Description: Number of period for the slow MA
%	optInSlowMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for slow MA
%	optInSignalPeriod: (Range from 1 to 100000) Description: Smoothing for the signal line (nb of period)
%	optInSignalMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for signal line
%
% Output
%	outMACD
%	outMACDSignal
%	outMACDHist
%
% See also: ta-lib

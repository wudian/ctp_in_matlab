function [outSlowK, outSlowD] = TA_STOCH ( high, low, close, FastKPeriod, SlowKPeriod, SlowKMA, SlowDPeriod, SlowDMA )
%
% Stochastic
%
% Required input parameters
%	high
%	low
%	close
%
% Optional input parameters
%	optInFastKPeriod: (Range from 1 to 100000) Description: Time period for building the Fast-K line
%	optInSlowKPeriod: (Range from 1 to 100000) Description: Smoothing for making the Slow-K line. Usually set to 3
%	optInSlowKMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for Slow-K
%	optInSlowDPeriod: (Range from 1 to 100000) Description: Smoothing for making the Slow-D line
%	optInSlowDMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for Slow-D
%
% Output
%	outSlowK
%	outSlowD
%
% See also: ta-lib

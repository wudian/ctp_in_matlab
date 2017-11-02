function [outFastK, outFastD] = TA_STOCHRSI ( inReal, TimePeriod, FastKPeriod, FastDPeriod, FastDMA )
%
% Stochastic Relative Strength Index
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInTimePeriod: (Range from 2 to 100000) Description: Number of period
%	optInFastKPeriod: (Range from 1 to 100000) Description: Time period for building the Fast-K line
%	optInFastDPeriod: (Range from 1 to 100000) Description: Smoothing for making the Fast-D line. Usually set to 3
%	optInFastDMA: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average for Fast-D
%
% Output
%	outFastK
%	outFastD
%
% See also: ta-lib

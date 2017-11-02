function [outRealUpperBand, outRealMiddleBand, outRealLowerBand] = TA_BBANDS ( inReal, TimePeriod, Deviationsup, Deviationsdown, MAType )
%
% Bollinger Bands
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInTimePeriod: (Range from 2 to 100000) Description: Number of period
%	optInDeviationsup: (Range from -3.000000e+37 to 3.000000e+37) Description: Deviation multiplier for upper band
%	optInDeviationsdown: (Range from -3.000000e+37 to 3.000000e+37) Description: Deviation multiplier for lower band
%	optInMAType: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average
%
% Output
%	outRealUpperBand
%	outRealMiddleBand
%	outRealLowerBand
%
% See also: ta-lib

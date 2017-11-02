function outReal = TA_SAREXT ( high, low, StartValue, OffsetonReverse, AFInitLong, AFLong, AFMaxLong, AFInitShort, AFShort, AFMaxShort )
%
% Parabolic SAR - Extended
%
% Required input parameters
%	high
%	low
%
% Optional input parameters
%	optInStartValue: (Range from -3.000000e+37 to 3.000000e+37) Description: Start value and direction. 0 for Auto, >0 for Long, <0 for Short
%	optInOffsetonReverse: (Range from 0.000000e+0 to 3.000000e+37) Description: Percent offset added/removed to initial stop on short/long reversal
%	optInAFInitLong: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor initial value for the Long direction
%	optInAFLong: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor for the Long direction
%	optInAFMaxLong: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor maximum value for the Long direction
%	optInAFInitShort: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor initial value for the Short direction
%	optInAFShort: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor for the Short direction
%	optInAFMaxShort: (Range from 0.000000e+0 to 3.000000e+37) Description: Acceleration Factor maximum value for the Short direction
%
% Output
%	outReal
%
% See also: ta-lib

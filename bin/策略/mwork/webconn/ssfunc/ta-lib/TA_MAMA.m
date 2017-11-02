function [outMAMA, outFAMA] = TA_MAMA ( inReal, FastLimit, SlowLimit )
%
% MESA Adaptive Moving Average
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInFastLimit: (Range from 1.000000e-2 to 9.900000e-1) Description: Upper limit use in the adaptive algorithm
%	optInSlowLimit: (Range from 1.000000e-2 to 9.900000e-1) Description: Lower limit use in the adaptive algorithm
%
% Output
%	outMAMA
%	outFAMA
%
% See also: ta-lib

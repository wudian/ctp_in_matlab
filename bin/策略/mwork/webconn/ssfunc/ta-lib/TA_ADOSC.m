function outReal = TA_ADOSC ( high, low, close, volume, FastPeriod, SlowPeriod )
%
% Chaikin A/D Oscillator
%
% Required input parameters
%	high
%	low
%	close
%	volume
%
% Optional input parameters
%	optInFastPeriod: (Range from 2 to 100000) Description: Number of period for the fast MA
%	optInSlowPeriod: (Range from 2 to 100000) Description: Number of period for the slow MA
%
% Output
%	outReal
%
% See also: ta-lib

function outReal = TA_PPO ( inReal, FastPeriod, SlowPeriod, MAType )
%
% Percentage Price Oscillator
%
% Required input parameters
%	inReal
%
% Optional input parameters
%	optInFastPeriod: (Range from 2 to 100000) Description: Number of period for the fast MA
%	optInSlowPeriod: (Range from 2 to 100000) Description: Number of period for the slow MA
%	optInMAType: (Range from ${optInArg.Range.Minimum} to ${optInArg.Range.Maximum}) Description: Type of Moving Average
%
% Output
%	outReal
%
% See also: ta-lib

function out = dsample(HLC, factor)
% Downsamples our time series by a given factor, preserving the HIGH and
% LOW fields' definition.  The input HLC is a numTicks-by-3 matrix, where
% each column corresponds to high prices, low prices, and closing prices,
% respectively.

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
HLC(:,1) = hhigh(HLC(:,1), factor);
HLC(:,2) =  llow(HLC(:,2), factor);

out = HLC(1:factor:end,:);
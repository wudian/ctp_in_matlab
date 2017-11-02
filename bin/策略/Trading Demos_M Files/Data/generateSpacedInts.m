function spacedInts = generateSpacedInts(lb, ub, number)
%GENERATESPACEDINTS Generates approximately NUMBER integers between LB and
% UB that are evenly spaced on a logarithmic scale.  It is "approximately"
% NUMBER because at the lower end of the series, rounding to the nearest
% integer may cause duplicates that are then weeded out.

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
spacedInts = unique(round(logspace(log10(lb), log10(ub), number)));



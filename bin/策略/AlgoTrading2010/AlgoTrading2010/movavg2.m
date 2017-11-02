function [lead,lag] = movavg(P,M,N,type) %#eml
% moving average, exponentially weighted.

%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
if type ~= 'e'
    error('MOVAVG:TYPE','This function only supports exponential moving averages')
end

L = length(P);

lead = zeros(size(P));
lag  = lead;

ws = 2/(M+1);
wl = 2/(N+1);

lead(1) = P(1);
lag(1)  = P(1);

% The for loop approach (slow for small-medium sized data series)
 for i = 2:L
     lead(i) = lead(i-1) + ws*(P(i) - lead(i-1));
     lag(i)  =  lag(i-1) + wl*(P(i) - lag(i-1));
 end
    
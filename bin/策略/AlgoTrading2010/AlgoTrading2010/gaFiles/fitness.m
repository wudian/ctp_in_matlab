function f = fitness(pop,indicator,price,scaling,cost)
%   See also tradeSignal, initializePopulation
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Generate Trading Signal from Population
s = tradeSignal(pop,indicator);
s = (s*2-1); % scale to +/-1 range
col = size(s,2);

%% PNL Caclulation
r  = [zeros(1,col);
    s(1:end-1,:).*repmat(diff(price),1,col)-abs(diff(s))*cost/2];
f = -scaling*sharpe(r,0);
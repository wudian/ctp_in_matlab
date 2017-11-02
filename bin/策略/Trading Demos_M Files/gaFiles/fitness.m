function [f,s,r] = fitness(pop,indicator,price,scaling,cost)
%   See also tradeSignal, initializePopulation
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
%% Generate Trading Signal from Population
indicator = (indicator + 1) / 2; % scale to 0/1 range
s = tradeSignal(pop,indicator);
s = (s*2-1); % scale to +/-1 range
col = size(s,2);

%% PNL Caclulation
trades  = [zeros(1,col); zeros(1,col); diff(s(1:end-1,:))]; % shift trading by 1 period
cash    = cumsum(-trades.*repmat(price,1,col)-abs(trades)*cost/2);
pandl   = [zeros(1,col); s(1:end-1,:)].*repmat(price,1,col) + cash;
r = [zeros(1,col); diff(pandl)];
    
f = -scaling*sharpe(r,0);
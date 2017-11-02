function sh = rsifun(x,data,scaling,cost)
% define rsi to accept vectorized inputs and return only sharpe ratio
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
if ~exist('scaling','var')
    scaling = 1;
end
if ~exist('cost','var')
    cost = 0;
end

[row,col] = size(x);
sh = zeros(row,1);
t   = length(data);
parfor i = 1:row
     if col > 3
            tindex = 1:x(i,4):t;
            % Calculate scaling parameter for time sampling
            sc = sqrt(scaling^2 / x(i,4));
        else
            tindex = 1:t;
            sc = scaling;
        end
    [~,~,sh(i)] = rsi(data(tindex),[x(i,1),x(i,2)],x(i,3),sc,cost);
end
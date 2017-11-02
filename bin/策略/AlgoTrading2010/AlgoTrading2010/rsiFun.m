function sh = rsifun(x,data,scaling,cost)
% define rsi to accept vectorized inputs and return only sharpe ratio
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
row = size(x,1);
sh = zeros(row,1);
parfor i = 1:row
    [~,~,sh(i)] = rsi(data,[x(i,1),x(i,2)],x(i,3),scaling,cost);
end
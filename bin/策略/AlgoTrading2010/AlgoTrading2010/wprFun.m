function sh = wprFun(x,data,scaling,cost)
% WPR wrapper
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.% define wpr to accept vectorized inputs and return only sharpe ratio

row = size(x,1);
sh = zeros(row,1);
parfor i = 1:row
    [~,~,sh(i)] = wpr(data,x(i,1),scaling,cost);
end
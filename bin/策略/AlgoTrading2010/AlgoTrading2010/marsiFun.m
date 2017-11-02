function sh = marsiFun(x,data,scaling,cost)
% define ma+rsi to accept vectorized inputs and return only sharpe ratio
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
row = size(x,1);
sh = zeros(row,1);
parfor i = 1:row
    if x(i,1) > x(i,2)
        sh(i) = NaN;
    else
        [~,~,sh(i)] = marsi(data,x(i,1),x(i,2),[x(i,3) x(i,4)],...
            x(i,5),scaling,cost);
    end
end
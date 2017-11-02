function sh = leadlagFun(x,data,scaling,cost)
% define leadlag to accept vectorized inputs and return only sharpe ratio
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
[row,col] = size(x);
sh  = zeros(row,1);
t   = length(data);
x = round(x);

if ~exist('scaling','var')
    scaling = 1;
end
if ~exist('cost','var')
    cost = 0;
end

% run simulation
parfor i = 1:row
    
    if x(i,1) > x(i,2)
        sh(i) = NaN;
    else
        if col > 2
            tindex = 1:x(i,3):t;
            % Calculate scaling parameter for time sampling
            sc = sqrt(scaling^2 / x(i,3));
        else
            tindex = 1:t;
            sc = scaling;
        end
        if x(i,1)> length(tindex) || x(i,2) > length(tindex)
            sh(i) = NaN;
        end
        [~,~,sh(i)] = leadlag(data(tindex), x(i,1), x(i,2),sc,cost);
    end
end
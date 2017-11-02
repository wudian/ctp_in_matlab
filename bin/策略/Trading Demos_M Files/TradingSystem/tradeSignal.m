function s = tradeSignal(pop,ind)
%TRADSIGNAL generates the trading signal from population
%   S = TRADESIGNAL(POP,IND) generates a trading signal (0 or 1) given the
%   rules specified in POP and the indicators in IND.  Rows of POP contain
%   distinct rules.  Columns of IND are different indicators.
%
%   An example rule defined in POP
%
%      0   |  0     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |   AND    | IND2 |   XOR    | IND3 |IND1  IND2 IND3|
%
%   Example
%   pop = [0 0 0 0 1 0 1 1 1 1;
%          1 0 0 0 1 0 1 1 1 1;
%          1 0 0 0 1 0 1 1 0 1;
%          1 0 0 0 1 0 1 0 1 1];
%   ind = [0 0 0;
%          0 0 1;
%          0 1 0;
%          0 1 1;
%          1 0 0;
%          1 0 1;
%          1 1 0;
%          1 1 1];
%   s = tradeSignal(pop,ind)
%
%   See also validRule, initializePopulation
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
%% BitString Length
L = size(pop,2);

%% Calculate Indicators
% Length = 4*NoIndicators - 2
I = (L+2)/4;

% indicator locations
indLoc = 1:3:L-I;
%% Generate Signal
s = zeros(size(ind,1),size(pop,1));
zed = ind == 0.5;
for r = 1:size(pop,1)
    signalsToUse = find(pop(r,L-I+1:end));
    idx = indLoc(signalsToUse);
    
    if length(idx) >= 1
        % use signal as is or its inverse
        C = double(ind(:,signalsToUse(1)) == pop(r, idx(1)));
        % Add back in the 0.5 values
        C( zed(:,signalsToUse(1))) = 0.5;
    end
    
    if length(idx) >= 2
        for i = 2:length(idx)
            A = C;
            % Indicator 2
            B = double(ind(:,signalsToUse(i)) == pop(r,idx(i)));
            % Connector
            conValue = bin2dec(num2str(pop(r,idx(i)+[-2 -1])));
            switch conValue
                case 0
                    cFun = @(v1,v2) and(v1,v2);
                case 1
                    cFun = @(v1,v2)  or(v1,v2);
                case 2
                    cFun = @(v1,v2) xor(v1,v2);
            end
            C = double(cFun(A,B));
            % Add back in the 0.5 values
            C( sum(zed(:,signalsToUse((i-1):i)))>0 ,:) = 0.5;
        end 
    end
    s(:,r) = C;
end


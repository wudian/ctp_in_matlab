function tf = validRule(rule)
%VALIDRULE determines if the rule is valid
%   TF = VALIDRULE(RULE) returns 1 if the rule is valid, 0 if
%   the rul is not valid.  RULE is the bit-string trading rule parent.
%
%   For example, a valid rule for 3 indicators can be
%
%      0   |  0     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   Invalid Rule with Connector Error (AND changed to 11, which is
%   undefind (only 00 = AND, 01 = OR, 10 = XOR are allowed).
%
%      0   |  1     1 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |   ???    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Extract indicators from rule length
if isvector(rule)
    L = length(rule); % column/row vector
else
    L = size(rule,2); % array
end
P = size(rule,1);
%% Calculate Indicators
% Length = 4*NoIndicators - 2
I = (L+2)/4;

%% Check for Valid Connectors
tf = false(P,1);
for i = 1:P
    for b = 2:3:L-I
        if sum(rule(i,[b b+1])) == 2
            tf(i) = false;
            break
        else
            tf(i) = true;
        end
    end
end

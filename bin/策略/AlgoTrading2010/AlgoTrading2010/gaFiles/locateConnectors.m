function [conIndex indIndex] = locateConnectors(rule);
%LOCATECONNECTORS finds locations of connectors in RULE
%   CONINDEX = LOCATECONNECTORS(RULE) returns the indicies into RULE that
%   are connectors.  For example, for 4 indicators and the rule:
%
%      0   |  0     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   the connector indicies are 2,3,5,6.
%
%  [CONIDEX,INDINDEX] = LOCATECONNECTORS(RULE) returns the inicies of the
%  indicator locations in INDINDEX.
%
%  Example:
%  pop = initializePopulation(4);
%  [c,ind] = locateConnectors(pop(1,:));
%
%  See also initializePopulation, validRule
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Extract indicators from rule length
if isvector(rule)
    L = length(rule); % column/row vector
else
    L = size(rule,2); % array
end

%% Calculate Indicators
% Length = 4*NoIndicators - 2
I = (L+2)/4;

%% Connector Locations
conIndex = [];
for b = 2:3:L-I
    conIndex = [conIndex b b+1];
end
%% Indicator Locations
indIndex = 1:L;
indIndex = indIndex(~ismember(indIndex,conIndex));


function pop = initializePopulation(I,popSize,J,K)
%INITIALIZEPOPULATION generates an initial population of 1's and 0's
%   POP = INITIALIZEPOPULATION(I) generates an intial population used for
%   genetic programming given the sequence of indicators specified in I.
%
%   I = vector of length 2 or a scalar
%
%   POP = binary values containing POPSIZE individuals of bit-string rules.
%   Default value of POPSIZE is 150.  POP is a matrix containing POPSIZE
%   rows of bitsrtings.
%
%   bit-string rule format:
%   indicator 1 | connector | indicator 2 | ... | inidcator N | Active
%
%   where Active is a binary number of length N that contains 1 for
%   indicators that are included and 0 for indicators that ar not.
%   Connector is a binary value that represents the boolean operator to
%   apply in the rule and values are
%
%       00 = AND
%       01 = OR
%       10 = XOR
%
%   POP = INITIALIZEPOPULATION(I,POPSIZE) specifies the number of strings
%   to generate.
%   
%   POP = INITIALIZEPOPULATION(I,POPSIZE,J,K) allows control of the maximum
%   and minimum number of indicators to use in each individual.
% 
%   J = minimum number of indicators to use (default is 2)
%   K = maximum number of indicators to use (default is length(I) or max(I))
%
%   Example
%   pop = initializePopulation(3,4);
%   
%   returns bit-string rules:
%   pop =
%      0     0     0     0     1     0     1     1     1     1
%    IND 1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%      1     1     0     0     1     0     0     1     1     1
%    IND 1 |   OR     | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%      0     0     0     0     0     0     0     0     1     1
%    IND 1 |   AND    | IND2 |    AND   | IND3 |IND1  IND2 IND3|
%      1     0     0     1     1     0     1     1     1     1
%    IND 1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%    <-----INDICATOR/CONNECTOR/RULE PART------>|<--STRUCTURE PART-->
%
%   See also
%
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Error checking/Defaults Values
if numel(I) > 2
    error('INITPOP:IndicatorError',...
         'Indicator specification must be a scalar or contain 2 elements');
end

if ~exist('popSize','var'), popSize = 150; end
if ~exist('J','var'), J = 2; end
if ~exist('K','var')
    K = max(I);
elseif K > max(I)   % check to make sure it isn't bigger than I
    warning('INITPOP:LargeK','K is to large, using max(I) = %d',max(I));
    K = max(I);
end

%% Generate Population
pop = [];
for ps = 1:popSize
    %% Number of Indicators
    u = randi([J K],1);
    
    %% Select Indicators to Use
    v = randperm(max(I));
    v = v(1:u);
    
    %% Generate Structure Part of Bit-String
    s = false(1,max(I)); % all zeros (0) initially
    s(v) = true;        % selected indicators are ones (1)
    
    %% Generate Condition Part of Bit-String
    r = logical(randi([0 1],1,u));
    c = false(1,max(I));
    c(s) = r;
    %% Generate Connector Part of Bit-String
    cn = randi([0 2],1,u-1);
    
    %% Build Bit-String
    cnb = logical([ 0 0 ]);
    bs = [];
    icn = 1;
    for i = 1:length(s)-1
        if s(i) == 1
            switch cn(icn)
                case 0
                    cnb = logical([0 0]);
                case 1
                    cnb = logical([0 1]);
                case 2
                    cnb = logical([1 0]);
            end
            icn = icn+1;
            if icn > length(cn)
                icn = icn -1;
            end
        end
        bs = [bs c(i) cnb];
    end
    bs  = [bs c(end) s];
    try
    pop = [pop; bs];
    catch
        disp('here')
    end
end %ps loop
%% Return logical valued population
pop = logical(pop);
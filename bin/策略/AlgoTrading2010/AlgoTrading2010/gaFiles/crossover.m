function xoverKids  = crossover(parents,options,GenomeLength,FitnessFcn,unused,thisPopulation)
%CROSSOVER generates kids from parents
%   KID = CROSSOVER(PARENTS,OPTIONS,GENOMELENGTH,FITNESSFCN,UNUSED,...
%                   THISPOPULATION)
%
%   produces offspring KIDS from PARENTS.  For example, take two parents:
%
%   Parent 1:
%      0   |  0     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   Parent 2:
%      1   |  1     0 |   1  |   1   0  |   1  |  1    1     1 |
%     IND1 |    OR    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   and a random index location where the crossover is to occur to be 3.
%   The resulting children will be:
%
%   Child 1:
%      1   |  1     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |    OR    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   Child 2:
%      0   |  0     0 |   1  |   1   0  |   1  |  1    1     1 |
%     IND1 |   AND    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   If the index for crossover were to fall on an indicator, say 4, the
%   resulting children would be.
%
%   Child 1:
%      1   |  1     0 |   1  |   1   0  |   1  |  1    1     1 |
%     IND1 |    OR    | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   Child 2:
%      0   |  0     0 |   0  |   1   0  |   1  |  1    1     1 |
%     IND1 |    AND   | IND2 |    OR    | IND3 |IND1  IND2 IND3|
%
%   Example:
%   pop = [ 0 0 0 0 1 0 1 1 1 1;
%           1 1 0 1 1 0 1 1 1 1 ];
%   GenomeLength = size(pop,2);
%   parents = [1 2];
%   kids = crossover(parents,[],GenomeLength,[],[],pop)
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
iterLimit = 1000;
% How many children to produce?
nKids = length(parents)/2;
% Allocate space for the kids
xoverKids = false(nKids,GenomeLength);

% valid connector/indicator locations
con = locateConnectors(thisPopulation(1,:));
index = 1;
for i=1:nKids
    % get parents
    r1 = parents(index);
    index = index+1;
    r2 = parents(index);
    index = index+1;
    
    valid = true;
    iter = 1;
    while valid
        % Randomly select one location for crossover from parents
        xoverPoints = randi(GenomeLength);
        % check if points are same type (connector or indicator)
        isCon = ismember(xoverPoints,con);
        if isCon % connectors
            xoverPoints(2) = con(ismember(con,[xoverPoints(1)-1 xoverPoints(1)+1]));
            xoverPoints = sort(xoverPoints);
        end
        
        % index for head/tail part
        head = 1:xoverPoints(end);
        tail = xoverPoints(end)+1:GenomeLength;
        
        % Split parents at connectors to create two new children
        kid(1,:) = [thisPopulation(r1,head) thisPopulation(r2,tail)];
        kid(2,:) = [thisPopulation(r2,head) thisPopulation(r1,tail)];
        
        valid = prod(double(~validRule(kid)));
        iter = iter+1;
        if iter > iterLimit
            error('CROSSOVER:ITERLIMIT', 'Iteration Limit Reached!')
        end
    end % while loop
    
    % randomly select one of the possible offspring to be used
    xoverKids(i,:) = kid(randi([1 2]),:);
end % kid loop

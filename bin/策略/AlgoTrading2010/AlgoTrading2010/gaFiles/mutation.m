function mutationChildren = mutation(parents,options,GenomeLength,FitnessFcn,state,thisScore,thisPopulation,mutationRate)
%MUTATION mutate childrend accordinlgy
%   MUTATIONCHILDREN = MUTATIONUNIFORM(PARENTS,OPTIONS,GENOMELENGTH,...
%                      FITNESSFCN,STATE,THISSCORE,THISPOPULATION, ...
%                      MUTATIONRATE)
%   Creates the mutated children using
%   uniform mutations at multiple points. Mutated genes are uniformly
%   distributed over the range of the gene. The new value is NOT a function
%   of the parents value for the gene.
%
%   Example:
%     options = gaoptimset('MutationFcn', @mutationuniform);
%
%   This will create an options structure specifying the mutation
%   function to be used is MUTATIONUNIFORM.  Since the MUTATIONRATE is
%   not specified, the default value of 0.01 is used.
%
%     mutationRate = 0.05;
%     options = gaoptimset('MutationFcn', {@mutationuniform, mutationRate});
%
%   This will create an options structure specifying the mutation
%   function to be used is MUTATIONUNIFORM and the MUTATIONRATE is
%   user specified to be 0.05.
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Error Checking/Default Values
if nargin < 8 || isempty(mutationRate)
    mutationRate = 0.02; % default mutation rate
end

if ~strcmpi(options.PopulationType,'bitString')
    error('MUTATION:NotBitStringType','PopulationType must be a bitString')
end

mutationChildren = false(length(parents),GenomeLength);

%% Select Parents to Mutate 
for i=1:length(parents)
    child = thisPopulation(parents(i),:);
    valid = true;
    while valid
        mutationPoints = find(rand(1,length(child)) < mutationRate);
        child(mutationPoints) = ~child(mutationPoints);
        valid = ~validRule(child);
    end
    mutationChildren(i,:) = child;
end
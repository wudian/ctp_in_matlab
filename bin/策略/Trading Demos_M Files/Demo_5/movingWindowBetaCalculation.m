function [beta,spread] = movingWindowBetaCalculation(p1 , p2 , numDays)
%function [beta,spread] = movingWindowBetaCalculation(p1 , p2 , numDays)
%

% Pre-allocate the beta results
beta = NaN(size(p2));

% Run in a loop
for i = numDays:length(p1)
    
    % Take a subset of the prices
    p1Sub = p1(i-numDays+1:i);
    p2Sub = p2(i-numDays+1:i,:);
    
    beta(i , :) = p2Sub \ p1Sub;
    
end

% Calculate the spread
spread = p1 - sum(beta .* p2 , 2);

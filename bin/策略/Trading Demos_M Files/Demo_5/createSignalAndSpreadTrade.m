function pnl = createSignalAndSpreadTrade(dates , close1 , close2 , cSpec1 , cSpec2 , params)
%function pnl = createSignalAndSpreadTrade(dates , close1 , close2 , cSpec1 , cSpec2 , params)
%

% pre-create pnl
pnl = nan;

% Pick out the number of days for regression
numDays = params.numDays;

% Some simple parameter checking to make sure that we have consistency
goodParamSet = true;
if ...
        (params.openPosition <= params.closePosition) || ...
        (params.openPosition <= params.closePosition) || ...
        (params.stopLoss <= params.openPosition)
    goodParamSet = false;
end

if ~goodParamSet
    return;
end

% Calculate the signal
[beta,spread] = ...
    movingWindowBetaCalculation(close1 , close2 , numDays);

% Trade
[~,pnl,~] = ...
    signalSpreadTrade(dates , spread , beta , close1 , close2 , cSpec1 , cSpec2 , params);

if isempty(pnl)
    pnl = nan;
end


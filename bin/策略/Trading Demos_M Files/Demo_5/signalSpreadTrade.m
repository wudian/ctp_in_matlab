function [dates,pnlVec,allTrades] = signalSpreadTrade(dates, spread , beta , price1 , price2 , cSpec1 , cSpec2 , params)
%function [dates,pnl] = signalSpreadTrade(spread , close1 , close2 , params)
%
% Uses the spread input to trade the assets in price1 and price2.

% Run everything through a loop. Before we do, we need to calculate the
% moving average and moving std of the signal
spreadMovAvg = movingAverage(spread , params.movAvgWindow);
spreadStdDev = movingStdDev(spread , params.stdDevWindow);

% Set up a vector of pnl
pnlVec = zeros(size(dates));

% Now, loop through, maintaining some items for logical purposes.
inPosition = false; position = 0;

% Start at the first non zero point (the wind up point)
startPoint = find(isnan(spreadMovAvg) , 1 , 'last') + 1;

% Flag that tells us if we can open - we will modify this after we go
% through what we perceive to be a stop loss
canWeOpen = true(size(dates));

% Keep all the trades
allTrades = [];

for i = startPoint:length(dates)
    
    if ~inPosition && canWeOpen(i)
        
        % Do we open a position?
        shortSignal = spreadMovAvg(i) + params.openPosition * spreadStdDev(i);
        longSignal  = spreadMovAvg(i) - params.openPosition * spreadStdDev(i);
        
        openPosition = false;
        if spread(i) > shortSignal
            openPosition = true;
            position = -1; % Gone short
        elseif spread(i) < longSignal
            openPosition = true;
            position = 1; % Gone long
        end
        
        if openPosition
            trade = iOpenPosition(position);
        end
        
    elseif inPosition
        
        % We need to analyse our trade spread based on the betas we opened
        % at
        tradeSpread = price1(i) - sum(trade.beta .* price2(i,:));
        
        % Check that we haven't violated stop loss criteria
        stopLoss = false;
        if trade.longPosition
            if tradeSpread < trade.stopLoss
                stopLoss = true;
            end
        else
            if tradeSpread > trade.stopLoss
                stopLoss = true;
            end
        end
        
        % Check for reversion
        reversion = false;
        if trade.longPosition
            if tradeSpread > trade.reversionLevel
                reversion = true;
            end
        else
            if tradeSpread < trade.reversionLevel
                reversion = true;
            end
        end
        
        % If one of the conditions above is true, then close position
        if ...
                stopLoss || ...
                reversion || ...
                (dates(i) - trade.openDate) > params.holdingPeriod || ...
                (i == length(dates));
            iClosePosition;
            allTrades = [allTrades trade]; %#ok<AGROW>
        end
        
%         Need to put the logic in here that stops us re-opening a position
%         after a stop loss
        if stopLoss
            if trade.longPosition
                % Look for the first position from now where we revert
                reversionLoc = find(spread(i:end) > trade.reversionLevel , 1 , 'first');
            else
                reversionLoc = find(spread(i:end) < trade.reversionLevel , 1 , 'first');
            end
            canWeOpen(i:i+reversionLoc) = false;
        end
        
    end
    
end

    function iClosePosition
        
        % Get the current prices
        priceClose = [price1(i) price2(i,:)];
        
        % Get the contract multipliers
        multipliers = [cSpec1.multiplier [cSpec2.multiplier]];
        
        % Pnl determined by (priceOpen - priceClose) * numContracts * longShort * multiplier
        positionBool = [1 -sign(trade.beta)];
        if trade.longShort ~= 1
            positionBool = -1 * positionBool;
        end
        
        % Record the closing prices and the current spread
        trade.priceClose = priceClose;
        trade.spreadClose = spread(i);
        
        % Generate the PnL
        pnlVec(i) = sum((priceClose - trade.priceOpen) .* positionBool .* trade.numContracts .* multipliers);
        
        % Switch off the position flag
        inPosition = false;
        
    end

    function trade = iOpenPosition(longShort)
        
        % Get the relevant number of contracts per leg
        priceVec = [price1(i) price2(i,:)];
        multipliers = [cSpec1.multiplier [cSpec2.multiplier]];
        betas = beta(i,:);
        numContracts = valueRatioPositionSizing(priceVec, multipliers , [1 betas] , true);
        
        trade.numContracts = numContracts;
        trade.longShort = longShort;
        trade.priceOpen = priceVec;
        trade.beta = beta(i,:);
        trade.openDate = dates(i);
        trade.spreadOpen = spread(i);
        
        if longShort == 1
            % Calculate our reversion and stop loss levels
            trade.reversionLevel = spreadMovAvg(i) - params.closePosition * spreadStdDev(i);
            trade.stopLoss = spreadMovAvg(i) - params.stopLoss * spreadStdDev(i);
            trade.longPosition = true;
        else
            trade.reversionLevel = spreadMovAvg(i) + params.closePosition * spreadStdDev(i);
            trade.stopLoss = spreadMovAvg(i) + params.stopLoss * spreadStdDev(i);
            trade.longPosition = false;
        end
        
        % switch on the positon flag
        inPosition = true;
        
    end

end

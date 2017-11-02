function pnlVec = runBacktestBatch(numDays , parComb , dates , close1 , close2 , cSpec1 , cSpec2)

% Pre-allocate the results
pnlVec = nan(size(parComb,1),1);

for i = 1:size(parComb,1)
    
    if (numDays == 60) && all(parComb(i,:) == [20.0000    1.0000    0.5000    4.0000    6.0000])
        hello = 1;
    end
    
    % Generate this specific results set
    params.numDays        = numDays;
    params.movAvgWindow   = parComb(i,1);
    params.stdDevWindow   = parComb(i,1);
    params.openPosition   = parComb(i,2);
    params.closePosition  = parComb(i,3);
    params.stopLoss       = parComb(i,4);
    params.holdingPeriod  = parComb(i,5);
    
    tmp = createSignalAndSpreadTrade(dates , close1 , close2 , cSpec1 , cSpec2 , params);
    pnlVec(i) = sum(tmp);
    
%     if mod(i,100) == 0
%       disp(sprintf('Done %d out of %d' , i , size(parComb,1)));
%     end

end
function sh = marsiwprFun(X,price,annualScaling,cost,best)
% MA + RSI + WPCTR
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
L = size(X,1);
sh = zeros(L,1);

parfor i = 1:L
    
    % Parse inputs
    N = X(i,1);
    M = X(i,2);
    P = X(i,3);
    Q = X(i,4);
    thresh = X(i,5);
    W = X(i,6);
    
    % trading signals
    sma = leadlag(price(:,end),N,M,annualScaling,cost);
    srs = rsi(price(:,end),[P Q],thresh,annualScaling,cost);
    swr = wpr(price,W,annualScaling,cost);
    
    % array of signals
    signals = [sma srs swr];
    
    % trading strategy
    s = tradeSignal(best,signals);
    s = (s*2-1); % scale to +/-1
    r  = [0; s(1:end-1).*diff(price(:,end))-abs(diff(s))*cost/2];
    sh(i) = annualScaling*sharpe(r,0);
end

if nargout == 0 % plot results
    
    % Parse inputs
    N = X(1,1);
    M = X(1,2);
    P = X(1,3);
    Q = X(1,4);
    thresh = X(1,5);
    W = X(1,6);
        % trading signals
    sma = leadlag(price(:,end),N,M,annualScaling,cost);
    srs = rsi(price(:,end),[P Q],thresh,annualScaling,cost);
    swr = wpr(price,W,annualScaling,cost);
    
    % array of signals
    signals = [sma srs swr];
    
    % trading strategy
    s = tradeSignal(best,signals);
    s = (s*2-1); % scale to +/-1
    r  = [0; s(1:end-1).*diff(price(:,end))-abs(diff(s))*cost/2];
    sh = annualScaling*sharpe(r,0);
    
    % plot  
    figure, leadlag(price(:,end),N,M,annualScaling,cost);
    figure, rsi(price(:,end),[P Q],thresh,annualScaling,cost);
    figure, wpr(price,W,annualScaling,cost);
        
    figure
    ax(1) = subplot(2,1,1);
    plot(price(:,end))
    title(['Evolutionary Learning Resutls, Sharpe Ratio = ',num2str(sh,3)])
    ax(2) = subplot(2,1,2);
    plot([s,cumsum(r)])
    legend('Position','Cumulative Return')
    title(['Final Return = ',num2str(sum(r),3), ...
        ' (',num2str(sum(r)/price(1,end)*100,3),'%)'])
    linkaxes(ax,'x');
end
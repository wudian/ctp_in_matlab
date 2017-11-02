function varargout = marsi(price,N,M,Mrsi,thresh,scaling,cost)
% MA+RSI in function call
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
if length(Mrsi) == 1
    Mrsi = [15*Mrsi Mrsi];
end

[sma,~,~,lead,lag] = leadlag(price,N,M,scaling,cost);
[srsi,~,~,ri,ma,thresh] = rsi(price,Mrsi,thresh,scaling,cost);

s = and((sma+1)/2,(srsi+1)/2)*2-1;
r  = [0; s(1:end-1).*diff(price)-abs(diff(s))*cost/2];
sh = scaling*sharpe(r,0);

if nargout == 0
    figure
    leadlag(price,N,M,scaling,cost);
    figure
    rsi(price,Mrsi,thresh,scaling,cost);
    
    figure
    ax(1) = subplot(3,1,1);
    plot([price,lead,lag,ma]), grid on
    legend('Price',['Lead ',num2str(N)],['Lag ',num2str(M)],...
        ['Mov. Avg.',num2str(Mrsi(1))])
    title(['MA+RSI Results, Sharpe Ratio = ',num2str(sh,3)])
    ax(2) = subplot(3,1,2);
    plot([ri,thresh(1)*ones(size(ri)),thresh(2)*ones(size(ri))])
    grid on
    legend(['RSI ',num2str(Mrsi(2))],'Lower Threshold','Upper Threshold')
    title('RSI')
    ax(3) = subplot(3,1,3);
    plot([s,cumsum(r)]), grid on
    legend('Position','Cumulative Return')
    title(['Final Return = ',num2str(sum(r),3),' (',num2str(sum(r)/price(1)*100,3),'%)'])
    linkaxes(ax,'x')
else
    %% Return values
    for i = 1:nargout
        switch i
            case 1
                varargout{1} = s; % signal
            case 2
                varargout{2} = r; % return (pnl)
            case 3
                varargout{3} = sh; % sharpe ratio
            case 4
                varargout{4} = ri; % rsi signal
            case 5
                varargout{5} = ma; % moving average
            otherwise
                warning('RSI:OutputArg',...
                    'Too many output arguments requested, ignoring last ones');
        end %switch
    end %for
end

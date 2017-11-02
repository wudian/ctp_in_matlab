function varargout = wpr(price,N,scaling,cost)
%WPR returns a trading signal for a simple Williams %R indicator
%   WPR returns a trading signal for a simple Williams %R indicator.
%
%   S = WPR(PRICE) returns a trading signal based upon a 14-period Williams
%   %R model. S is the trading signal of values -1, 0, 1 where -1 denotes a
%   sell (short), 0 is neutral, and 1 is buy (long).
%
%   S = WPR(PRICE,N) returns a trading signal for a N-period model.
%
%   S = WPR(PRICE,N,scaling,cost) incorporates an annual scaling (used when
%   computing the Shapre ratio) and a bid/ask spread transaction cost
%   (assumed constant)
%
%   [S,R,SH,W] = WPR(...) returns the trading signal S, the absolute return
%   in R, the Sharpe Ratio in SH calculated using R, and the indicator W.
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
if ~exist('scaling','var'), scaling = 1; end
if ~exist('N','var'), N = 14; end
if ~exist('cost','var'), cost = 0; end

%% williams %r
w = willpctr(price,N);

%% Position signal
s = zeros(size(w));
% Crossing the lower threshold on the reversion
indx    = w < -80;
indx    = [false; indx(1:end-1) & ~indx(2:end)];
s(indx) = 1;
% Crossing the upper threshold on the reversion
indx    = w > -20;
indx    = [false; indx(1:end-1) & ~indx(2:end)];
s(indx) = -1;
% Fill in zero values with prior position
for i = 2:length(s)
    if  s(i) == 0
        s(i) = s(i-1);
    end
end

%% PNL calculation
trades  = [0; 0; diff(s(1:end-1))]; % shift trading by 1 period
cash    = cumsum(-trades.*price(:,end)-abs(trades)*cost/2);
pandl   = [0; s(1:end-1)].*price(:,end) + cash;
r = diff(pandl);
sh = scaling*sharpe(r,0);
%% Plot if requested
if nargout == 0
    ax(1) = subplot(3,1,1);
    plot(price), grid on
    legend('High','Low','Close')
    title(['W%R Results, Sharpe Ratio = ',num2str(sh,3)])
    ylabel('Price (USD)')
    ax(2) = subplot(3,1,2);
    plot([w,-80*ones(size(w)),-20*ones(size(w))])
    grid on
    legend(['Williams %R ',num2str(N)],'Over sold','Over bought')
    title('W%R')
    ylabel('W%R')
    ax(3) = subplot(3,1,3);
    plot([s,pandl]), grid on
    legend('Position','Cumulative Return')
    title(['Final Return = ',num2str(sum(r),3),' (',num2str(sum(r)/price(1)*100,3),'%)'])
    ylabel('Return (USD)')
    xlabel('Serial time number')
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
                varargout{4} = w; % w%r signal
            otherwise
                warning('WPR:OutputArg',...
                    'Too many output arguments requested, ignoring last ones');
        end %switch
    end %for
end %if
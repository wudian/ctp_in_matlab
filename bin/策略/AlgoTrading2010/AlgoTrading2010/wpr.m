function varargout = wpr(price,N,scaling,cost)
%
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
if ~exist('scaling','var'), scaling = 1; end
if ~exist('N','var'), N = 14; end
if ~exist('cost','var'), cost = 0; end

%% williams %r
w = willpctr(price,N);

%% generate signal
s = ones(size(w));
s(w<-50) = -1;

%% PNL calculation
r  = [0; s(1:end-1).*diff(price(:,end))-abs(diff(s))*cost/2];
sh = scaling*sharpe(r,0);

%% Plot if requested
if nargout == 0
    ax(1) = subplot(3,1,1);
    plot(price), grid on
    legend('High','Low','Close')
    title(['W%R Results, Sharpe Ratio = ',num2str(sh,3)])
    ax(2) = subplot(3,1,2);
    plot([w,-80*ones(size(w)),-20*ones(size(w))])
    grid on
    legend(['Williams %R ',num2str(N)],'Over sold','Over bought')
    title('W%R')
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
                varargout{4} = w; % w%r signal
            otherwise
                warning('WPR:OutputArg',...
                    'Too many output arguments requested, ignoring last ones');
        end %switch
    end %for
end %if
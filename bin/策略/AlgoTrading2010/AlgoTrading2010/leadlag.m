function varargout = leadlag(P,N,M,scaling,cost)
%LEADLAG returns a trading signal for a simple lead/lag ema indicator
%   LEADLAG returns a trading signal for a simple lead/lag exponential
%   moving-average technical indicator.
%
%   S = LEADLAG(PRICE) returns a trading signal based upon a 12-period
%   lead and a 26-period lag.  This is the default value used in a MACD
%   indicator.  S is the trading signal of values -1, 0, 1 where -1 denotes
%   a sell (short), 0 is neutral, and 1 is buy (long).
%
%   S = LEADLAG(PRICE,N,M) returns a trading signal for a N-period lead and
%   a M-period lag.
%
%   [S,R,SH,LEAD,LAG] = LEADLAG(...) returns the trading signal S, the
%   absolute return in R, the Sharpe Ratio in SH calcualted using R, and
%   the LEAD or LAG series.
%
%   EXAMPLE:
%   % IBM
%     load ibm.dat
%     [s,~,~,lead,lag] = leadlag(ibm(:,4));
%     ax(1) = subplot(2,1,1);
%     plot([ibm(:,4),lead,lag]);
%     title('IBM Price Series')
%     legend('Close','Lead','Lag','Location','Best')
%     ax(2) = subplot(2,1,2);
%     plot(s)
%     title('Trading Signal')
%     set(gca,'YLim',[-1.2 1.2])
%     linkaxes(ax,'x')
%
%   % Disney
%     load disney
%     dis_CLOSE(isnan(dis_CLOSE)) = [];
%     [s,~,~,lead,lag] = leadlag(dis_CLOSE);
%     ax(1) = subplot(2,1,1);
%     plot([dis_CLOSE,lead,lag]);
%     title('Disney Price Series')
%     legend('Close','Lead','Lag','Location','Best')
%     ax(2) = subplot(2,1,2);
%     plot(s)
%     title('Trading Signal')
%     set(gca,'YLim',[-1.2 1.2])
%     linkaxes(ax,'x')
%
%   See also movavg, sharpe, macd

%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.

%% Process input args
if ~exist('scaling','var')
    scaling = 1;
end

if ~exist('cost','var')
    cost = 0;
end

if nargin < 2
    % defualt values
    M = 26;
    N = 12;
elseif nargin < 3
    error('LEADLAG:NoLagWindowDefined',...
        'When defining a leading window, the lag must be defined too')
end %if

%% Simple lead/lag ema calculation
if nargin > 0
    s = zeros(size(P));
    [lead,lag] = movavg(P,N,M,'e');
    s(lead>lag) = 1;
    s(lag>lead) = -1;
    r  = [0; s(1:end-1).*diff(P)-abs(diff(s))*cost/2];
    sh = scaling*sharpe(r,0);
    
    if nargout == 0 % Plot
        %% Plot results
        ax(1) = subplot(2,1,1);
        plot([P,lead,lag]); grid on
        legend('Close',['Lead ',num2str(N)],['Lag ',num2str(M)],'Location','Best')
        title(['Lead/Lag EMA Results, Annual Sharpe Ratio = ',num2str(sh,3)])
        ax(2) = subplot(2,1,2);
        plot([s,cumsum(r)]); grid on
        legend('Position','Cumulative Return','Location','Best')
        title(['Final Return = ',num2str(sum(r),3),' (',num2str(sum(r)/P(1)*100,3),'%)'])
        linkaxes(ax,'x')
    else
        for i = 1:nargout
            switch i
                case 1
                    varargout{1} = s;
                case 2
                    
                    varargout{2} = r;
                case 3
                    varargout{3} =  sh;
                case 4
                    varargout{4} = lead;
                case 5
                    varargout{5} = lag;
                otherwise
                    warning('LEADLAG:OutputArg',...
                        'Too many output arguments requested, ignoring last ones');
            end %switch
        end %for
    end %if
else
    %% Run Example
    example(1:2)
end %if

%% Examples
function example(ex)
for e = 1:length(ex)
    for e = 1:length(ex)
        switch ex(e)
            case 1
                figure(1), clf
                load ibm.dat
                [s,~,~,lead,lag] = leadlag(ibm(:,4));
                ax(1) = subplot(2,1,1);
                plot([ibm(:,4),lead,lag]);
                title('IBM Price Series')
                legend('Close','Lead','Lag','Location','Best')
                ax(2) = subplot(2,1,2);
                plot(s)
                title('Trading Signal')
                set(gca,'YLim',[-1.2 1.2])
                linkaxes(ax,'x')
            case 2
                figure(2),clf
                load disney
                dis_CLOSE(isnan(dis_CLOSE)) = [];
                [s,~,~,lead,lag] = leadlag(dis_CLOSE);
                ax(1) = subplot(2,1,1);
                plot([dis_CLOSE,lead,lag]);
                title('Disney Price Series')
                legend('Close','Lead','Lag','Location','Best')
                ax(2) = subplot(2,1,2);
                plot(s)
                title('Trading Signal')
                set(gca,'YLim',[-1.2 1.2])
                linkaxes(ax,'x')
        end %switch
    end %for
end %for
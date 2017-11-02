function varargout = rsi(price,M,thresh,scaling,cost)
% RSI
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
if ~exist('scaling','var')
    scaling = 1;
end
if ~exist('M','var')
    M = 0; % no detrending
else
    if numel(M) > 1
        N = M(2);
        M = M(1);
    else
        N = M;
        M = 15*M;
    end
end
if ~exist('thresh','var')
    thresh = [30 70]; % default threshold
else
    if numel(thresh) == 1 % scalar value
        thresh = [100-thresh, thresh];
    else
        if thresh(1) > thresh(2)
            thresh= thresh(2:-1:1);
        end
    end
end

if ~exist('cost','var')
    cost = 0; % default cost
end

%% Detrend with a moving average
if M == 0
    ma = zeros(size(price));
else
    ma = movavg(price,M,M,'e');
end
ri = rsindex(price - ma, N);

%% Position signal
s = zeros(size(price));
% Crossing the lower threshold
indx    = ri < thresh(1);
indx    = [false; indx(1:end-1) & ~indx(2:end)];
s(indx) = 1;
% Crossing the upper threshold
indx    = ri > thresh(2);
indx    = [false; indx(1:end-1) & ~indx(2:end)];
s(indx) = -1;
% Fill in zero values with prior position
for i = 2:length(s)
    if  s(i) == 0
        s(i) = s(i-1);
    end
end

%% PNL Caclulation
r  = [0; s(1:end-1).*diff(price)-abs(diff(s))*cost/2];
sh = scaling*sharpe(r,0);

%% Plot if requested
if nargout == 0
    ax(1) = subplot(3,1,1);
    plot([price,ma]), grid on
    legend('Price',['Moving Average ',num2str(M)])
    title(['RSI Results, Sharpe Ratio = ',num2str(sh,3)])
    ax(2) = subplot(3,1,2);
    plot([ri,thresh(1)*ones(size(ri)),thresh(2)*ones(size(ri))])
    grid on
    legend(['RSI ',num2str(N)],'Lower Threshold','Upper Threshold')
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
            case 6
                varargout{6} = thresh; % threshold
            otherwise
                warning('RSI:OutputArg',...
                    'Too many output arguments requested, ignoring last ones');
        end %switch
    end %for
end %if

%% Examples


%% Supporting Functions
% Faster implementation of rsindex found in Financial Toolbox
function r=rsindex(x,N)
L = length(x);
dx = diff([0;x]); 
up=dx;
down=abs(dx);
% up and down moves
I=dx<=0;
up(I) = 0;
down(~I)=0;
% calculate exponential moving averages
m1 = movavg(up,N,N,'e'); m2 = movavg(down,N,N,'e');
warning off
r = 100*m1./(m1+m2);
%r(isnan(r))=50;
I2=~((up+down)>0);
r(I2)=50;

warning on
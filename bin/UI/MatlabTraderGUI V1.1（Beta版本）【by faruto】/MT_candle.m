function MT_candle(hi, lo, cl, op, color, dates, dateform)
% Modified by LiYang 2011/12/28
% Email:farutoliyang@gmail.com
%CANDLE Candlestick chart.
%
%   CANDLE(HI, LO, CL, OP)
%   CANDLE(HI, LO, CL, OP, COLOR, DATES, DATEFORM)
%
%   Optional Inputs: COLOR, DATES, DATEFORM
%
%   Inputs:
%         HI - Column vector of high prices of a security.
%
%         LO - Column vector of low prices of a security.
%
%         CL - Column vector of closing prices of a security.
%
%         OP - Column vector of opening prices of a security.
%
%   Optional Inputs:
%      COLOR - Three element color vector, [R G B], or a string specifying the
%              color name. MATLAB supplies a default color if none is specified
%              or if it is empty. The default color differs depending on the
%              background color of the figure window. See COLORSPEC in the
%              MATLAB Reference Guide for color names.
%
%      DATES - Column vector of dates for user specified X-axis tick
%              labels.
%
%   DATEFORM - A scalar dictating the format of the date string tick labels.
%              See DATEAXIS for details on the date string formats.
%
%   See also BOLLING, HIGHLOW, MOVAVG, POINTFIG.

%	Copyright 1995-2006 The MathWorks, Inc.
%	$Revision: 1.9.2.5 $   $Date: 2010/10/08 16:43:09 $

if nargin < 5 || isempty(color)
    cls = get(gca, 'colororder');
    color = cls(1, :);
end

if nargin < 4
    error(message('finance:candle:missingInputs'))
end

if size(hi, 2) > 1 || size(lo, 2) > 1 || size(cl, 2) > 1 || size(op, 2) > 1
    error(message('finance:candle:invalidInputs'))

elseif size(hi, 1) ~= size(lo, 1) || size(lo, 1) ~= size(cl, 1) || size(cl, 1) ~= size(op, 1),
    error(message('finance:candle:mismatchInputData'));
end

if nargin == 6 || nargin == 7
    if size(dates, 2) ~= 1
        error(message('finance:candle:invalidDateSize'));

    elseif size(dates, 1) ~= size(hi, 1)
        error(message('finance:candle:mismatchDatesData'));
    end
end

back = get(gca, 'color');

% Determine if current plot is held or not
if ishold
    hldflag = 1;

else
    hldflag = 0;
end

m = length(hi(:));

% Need to pad all inputs with NaN's to leave spaces between day data
tmp = nan;
nanpad = tmp(1, ones(1, m));
hilo = [hi'; lo'; nanpad];
index = 1:m;
indhilo = index(ones(3, 1), :);
%% =========================================
% plot(indhilo(:), hilo(:), 'color', color)
% Modified by LiYang 2011/12/28
x = indhilo(:);
y = hilo(:);
for i = 1:length(cl)
    ind = (i*3-2):(i*3);
    if cl(i)>=op(i)
        plot( x(ind),y(ind),'r' );
        hold on;
    else
        plot( x(ind),y(ind),'g' );
        hold on;
    end
end
% plot(indhilo(:), hilo(:), 'color', color);
%% =========================================
clpad = [cl(:)';nanpad];
clpad = clpad(:)';
oppad = [op(:)'; nanpad];
oppad = oppad(:)';

% Create boundaries for filled regions
xbottom = index - 0.25;
xbotpad = [xbottom(:)'; nanpad];
xbotpad = xbotpad(:)';
xtop = index + 0.25;
xtoppad = [xtop(:)'; nanpad];
xtoppad = xtoppad(:)';
ybottom = min(clpad, oppad);
ytop = max(clpad, oppad);

% Plot lines between high and low price for day
hold on

% z-data used to stagger layering. This prevents renderer layering issues.
zdata = xtoppad;
zdata(~isnan(zdata)) = .01;
zdata2 = zdata + .01;
 
% Plot box representing closing and opening price span
% If the opening price is less than the close, box is empty
i = find(oppad(:) <= clpad(:));
%% =========================================
% 'edgecolor', 'r' 
% Modified by LiYang 2011/12/28
boxes(i) = patch([xbotpad(i); xbotpad(i); xtoppad(i); xtoppad(i)],...
    [ytop(i); ybottom(i); ybottom(i); ytop(i)], ...
    [zdata(i); zdata(i); zdata(i); zdata(i)], ...
    back, 'edgecolor', 'r');
%% =========================================

% If the opening price is greater than the close, box is filled
i = find(oppad(:) > clpad(:));
%% =========================================
% 'edgecolor', 'g' 
% Modified by LiYang 2011/12/28
boxes(i) = patch([xbotpad(i); xbotpad(i); xtoppad(i); xtoppad(i)],...
    [ytop(i); ybottom(i); ybottom(i); ytop(i)],...
    [zdata2(i); zdata2(i); zdata2(i); zdata2(i)], ...
    'g', 'edgecolor', 'g'); %#ok
%% =========================================

setappdata(gca, 'plottype', 'Candle ')        % set tag for use with timeser.m

% Add support for providing dates.
% if nargin == 6 || nargin == 7
%     dateset = dates;
% 
%     hcdl_vl = findobj(gca, 'Type', 'line');
%     hcdl_bx = findobj(gca, 'Type', 'patch');
% 
%     % The CANDLE plot is made up of patch(es) and a line.  hcdl_vl is the
%     % handle to the vertical lines; it's actually only 1 line object.
%     % hcdl_bx contains the handle(s) of the patch object(s) that make up the
%     % empty and filled boxes.  The XData of those objects need to be changed
%     % to dates so that ZOOM works correctly.
%     line_xdata = get(hcdl_vl, 'XData');
%     set(hcdl_vl, 'XData', dateset(line_xdata));
%     for pidx=1:length(hcdl_bx),   % Need to do loop since there can be 1 or 2 patches.
%         patch_xdata = get(hcdl_bx(pidx), 'XData');
%         offset = [-0.25*ones(2, size(patch_xdata, 2)); ...
%             +0.25*ones(2, size(patch_xdata, 2))] * min(abs(diff(dateset)));
%         set(hcdl_bx(pidx), 'XData', dateset(round(patch_xdata))+offset);
%     end
% 
%     % Change XTickLabel to date string format.
%     if ~exist('dateform', 'var') || isempty(dateform)
%         datetick('x');
% 
%     else
%         datetick('x', dateform);
%     end
% end


% If original figure was not held, turn hold off
if ~hldflag
    hold off
end

%% =========================================
% 更改x轴为时间轴
if length(dates)>4
    step = 4;
else
    step = length(dates);
end

    newTick = linspace(1,length(dates),step)';
    newTick = floor(newTick);
    newTickChar = datestr(dates(newTick));
    newTickLabel = cell(step,1);
    for i = 1:step
        newTickLabel{i,1} = newTickChar(i,:);
    end

set(gca,'XTick',newTick);
set(gca,'XTickLabel',newTickLabel);
%% =========================================
% 画出最高点和最低点
% [Highest,hind] = max(hi);
% [Lowest,lind] = min(lo);
% hold on;
% text(hind,Highest,['\leftarrow',num2str(Highest)]);
% text(lind,Lowest,['\leftarrow',num2str(Lowest)]);

%[EOF]

function BandTrader(tick)
%BANDTRADER - Band Trading Strategy
%
%  This MATLAB function implements a simple band trading strategy. A band 
%  consists of two lines that form the upper and lower boundaries of the band. 
%  The upper and lower boundaries are used to to enter and exit trades.
%  For example, if prices fall below the lower boundary a buy signal is 
%  generated.
% 
%  Requirements:
%  - MATLAB 2012b
%  - TA Developer Toolbox (http://www.tadeveloper.com)
%
%  Please refer to http://www.tadeveloper.com/docs/80-matlab-algo-trading
%  for a full description of the strategy

movingAverage = 10;
bandWidth = 2;

% Construct the center line
Average = (tick.HighestPrice + tick.LowestPrice)/2;
CenterLine = Ema(Average, movingAverage);
PlotDataSeries(sys, CenterLine, 'blue', 'solid', 2, '');
  
% Construct the bands
AverageTrueRange = Atr(sys.BarData, movingAverage);  
UpperBand = CenterLine + bandWidth * AverageTrueRange;
LowerBand = CenterLine - bandWidth * AverageTrueRange;
PlotDataSeries(sys, UpperBand, 'magenta', 'solid', 2, '');
PlotDataSeries(sys, LowerBand, 'magenta', 'solid', 2, '');
  
% Entry and Exit Signals
LongSignal = sys.Close < LowerBand;
ShortSignal = sys.Close > UpperBand;
AddLongSignal(sys, LongSignal);
AddShortSignal(sys, ShortSignal);  

end
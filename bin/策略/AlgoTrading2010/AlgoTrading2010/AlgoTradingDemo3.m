%% Algorithmic Trading with MATLAB(R): Evolutionary Learning
% In <AlgoTradingDemo2.html AlgoTradingDemo2.m> we saw how to add two
% signals together to get improved results.  In this demo we'll use
% evolutionary learning (genetic algorithm) to select our signals and
% the logic used to build the trading strategy.
%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Load in the data
% Again, we'll import Bund data sampled minutely
load bund1min
testPts = floor(0.8*length(data(:,4)));
step = 30; % 30 minute interval
BundClose = data(1:step:testPts,4);
BundCloseV = data(testPts+1:step:end,4);
annualScaling = sqrt(250*60*11/step);
cost = 0.01;
addpath('gaFiles')

%% Replicate the MA+RSI approach using evolutionary learning
% First gather the indicator signals for the training set
N = 2; M = 396; thresh = 55; P = 2; Q = 110;
sma = leadlag(BundClose,N,M,annualScaling,cost);
srs = rsi(BundClose,[P,Q],thresh,annualScaling,cost);
marsi(BundClose,N,M,[P,Q],thresh,annualScaling,cost)

signals = [sma srs];
names = {'MA','RSI'};
%% Trading signals
% Plot the "state" of the market represented by the signals
figure
ax(1) = subplot(2,1,1); plot(BundClose);
ax(2) = subplot(2,1,2); imagesc(signals')
cmap = colormap([1 0 0; 0 0 1; 0 1 0]);
set(gca,'YTick',1:length(names),'YTickLabel',names);
linkaxes(ax,'x');

%% Generate initial population
% Generate initial population of signals we'll use to seed the search
% space.
close all
I = size(signals,2);
pop = initializePopulation(I);
imagesc(pop)
xlabel('Bit Position'); ylabel('Individual in Population')
colormap([1 0 0; 0 1 0]); set(gca,'XTick',1:size(pop,2))
%% Fitness Function
% Objective is to find a target bitstring (minimum value of -Sharpe Ratio)
type fitness
%%
% Objective function definition as a function handle (the optimization
% sovlers need a function as an input, this is how to define them)
obj = @(pop) fitness(pop,signals,BundClose,annualScaling,cost)
%%
% Evaluate objective for initial population
obj(pop)
%% Solve With Genetic Algorithm
% Find best trading rule and maximum Sharpe ratio (min -Sharpe ratio)
options = gaoptimset('Display','iter','PopulationType','bitstring',...
    'PopulationSize',size(pop,1),...
    'InitialPopulation',pop,...
    'CrossoverFcn', @crossover,...
    'MutationFcn', @mutation,...
    'PlotFcns', @plotRules,...
    'Vectorized','on');

[best,minSh] = ga(obj,size(pop,2),[],[],[],[],[],[],[],options)

%% Evaluate Best Performer
s = tradeSignal(best,signals);
s = (s*2-1); % scale to +/-1
r  = [0; s(1:end-1).*diff(BundClose)-abs(diff(s))*cost/2];
sh = annualScaling*sharpe(r,0);

% Plot results
figure
ax(1) = subplot(2,1,1);
plot(BundClose)
title(['Evolutionary Learning Resutls, Sharpe Ratio = ',num2str(sh,3)])
ax(2) = subplot(2,1,2);
plot([s,cumsum(r)])
legend('Position','Cumulative Return')
title(['Final Return = ',num2str(sum(r),3), ...
    ' (',num2str(sum(r)/BundClose(1)*100,3),'%)'])
linkaxes(ax,'x');
%%
% Note that this results is the same as found in (<AlgoTradingDemo2.html#9
% AlgoTradingDemo2.m>).  This validates the evolutionary approach can be
% used to select a trading strategy.  We'll now add another signal to the
% mix and see if this appraoch will find a better solution.  But first,
% we'll rerun the validation set to make sure we're consistent with the
% earlier result.

%% Check validation set
sma = leadlag(BundCloseV,N,M,annualScaling,cost);
srs = rsi(BundCloseV,[P Q],thresh,annualScaling,cost);
marsi(BundCloseV,N,M,[P Q],thresh,annualScaling,cost)

signals = [sma srs];
s = tradeSignal(best,signals);
s = (s*2-1); % scale to +/-1
r  = [0; s(1:end-1).*diff(BundCloseV)-abs(diff(s))*cost/2];
sh = annualScaling*sharpe(r,0);

% Plot results
figure
ax(1) = subplot(2,1,1);
plot(BundCloseV)
title(['Evolutionary Learning Resutls, Sharpe Ratio = ',num2str(sh,3)])
ax(2) = subplot(2,1,2);
plot([s,cumsum(r)])
legend('Position','Cumulative Return')
title(['Final Return = ',num2str(sum(r),3), ...
    ' (',num2str(sum(r)/BundCloseV(1)*100,3),'%)'])
linkaxes(ax,'x');
%%
% On to the next demo: <AlgoTradingDemo4.html AlgoTradingDemo4.m>

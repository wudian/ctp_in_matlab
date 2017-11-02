%% Algorithmic Trading with MATLAB(R): Profiling and C-Code Generation
% This demo shows how to profile your code to find the performance
% bottlenecks, or areas for improvement, as well as the capability to
% generate C-Code from MATLAB.
%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% Load in the data
% Bund future data - 1 minute intervals
load bund1min
step = 30;
annualScaling = sqrt(250*60*11/step);
cost = 0.01;
BundClose = data(1:step:end,end);

%% Profile the MARSI code
% Let's find the slowest part of the MARSI code.

N = 2; M = 396; thresh = 55; P = 2; Q = 110;
profile on
marsi(BundClose,N,M,[P Q],thresh,annualScaling,cost)
profile viewer
result = profile('info');
profile off
% movavg was the bottleneck, take a look TotalTime for it
result.FunctionTable(4)

%% Improve movavg code and re-profile
% Use the function in movavg2.m to shadow the financial toolbox |movavg|
% function and profile again.  Note that we are using embedded MATLAB to
% generate the mex (MATLAB Executable) file and will later use it to
% generate portable C-code.
system('copy movavg2.m movavg.m')
type movavg
profile on
marsi(BundClose,N,M,[P Q],thresh,annualScaling,cost)
profile viewer
result2 = profile('info');
result2.FunctionTable(4)
%%
% Nearly 7% speed up in recoding the 2 for loops to 1 for loop.
speedUp = result.FunctionTable(4).TotalTime/result2.FunctionTable(4).TotalTime

%% Now lets compile it into a mex file and run it again
% Note that you will need to set up your compiler first (through |mex -
% setup|)
emlmex movavg.m -eg {BundClose,N,M,'e'}
profile on
marsi(BundClose,N,M,[P Q],thresh,annualScaling,cost)
profile viewer
result3 = profile('info');
result3.FunctionTable(4)

%%
% A 32X speedup over for loop, and 30X speedup over vectorized version!
speedUpFor = result.FunctionTable(4).TotalTime/result3.FunctionTable(4).TotalTime
speedUpVect = result2.FunctionTable(4).TotalTime/result3.FunctionTable(4).TotalTime

%% Generating portable C-code
% You can also generate portable C-code to target a different hardware
% platform or use the C-code in a real-time environment.  Here is how to do
% it for the movavg function (I leave marsi as an exercise for interested
% readers).
emlc -report movavg.m -eg {BundClose,N,M,'e'}
%%
% The generated C-code is in the emcprj folder.  Here is the listing of the
% entry point:
type emcprj\mexfcn\movavg\movavg.c
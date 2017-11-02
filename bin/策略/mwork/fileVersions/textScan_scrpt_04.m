%% Clean work
tic; clear; clc; close all;
%% Inputs and Parameters
cd F:\mwork;
filename = 'SHSZ14.txt';
si = 6; % Sample Interval
s = 5; % Select Top_N for each tick, store'em in 
rsb = 100; % Threthhold
%% Initialize and Dir monitoring
nt = 240*(60/si) + 1;  % Number of time ticks
fh = dir([pwd,['\',filename]]);
%t0 = datevec(fh.date,'dd-mmm-yyyy HH:MM:SS'); % File time stamp
%% File Scanning
formatSpec = '%s';
nf = 1;
fileID = fopen(filename);
C_text = textscan(fileID,formatSpec,nf,'delimiter','\n');
D = textscan(fileID,'%s %s %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %d %d %d %d %d','delimiter',',');
fclose(fileID);
%% Variables initialize
ns = length(D{1,1});
t0 = zeros(1,6); % File time stamp
DP = zeros(ns,nt); % Price Matrix
DSV = zeros(ns,nt); % S Vol
DBV = zeros(ns,nt); % B Vol
SBR = zeros(ns,nt); % S/B Ratio
SS = zeros(s,nt);
sbr_topN = zeros(s,1);
% Define UserData Struct for Timer Obj
scanTimes = 0; 
UD = struct('filename',filename,'si',si,'t0',t0,'DP',DP,'DSV',DSV,'DBV',DBV,'SBR',SBR,'SS',SS,'sbr_topN',sbr_topN,'rsb',rsb,'scanTimes',scanTimes);
%% Create the timer obj
t = timer('TimerFcn', @tFcn_rtss, ...
    'Period', 3, ...
    'TasksToExecute',500000,...
    'ExecutionMode', 'fixedRate', ...
    'StartDelay', 0.1, ...
    'UserData', UD);
start(t);
UD = get(t, 'UserData');


%pause(50);
%delete(t);
%% Record Time
toc;

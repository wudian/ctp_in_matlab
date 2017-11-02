%% Clean work
tic; clear; clc; close all;
%% Inputs and Parameters
cd F:\mwork;
filename = 'SHSZ10.txt';
si = 6; % Sample Interval
s = 5; % Select Top_N for each tick, store'em in 
%% Initialize
nt = 240*(60/si) + 1;
fh = dir([pwd,['\',filename]]);
t0 = datevec(fh.date,'dd-mmm-yyyy HH:MM:SS');
%% File Scanning
fileID = fopen(filename);
formatSpec = '%s';
nf = 1;
C_text = textscan(fileID,formatSpec,nf,'delimiter','\n');
D = textscan(fileID,'%s %s %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %d %d %d %d %d','delimiter',',');
fclose(fileID);
%% Variables initialize
ns = length(D{1,1});
DP = zeros(ns,nt); % Price Matrix
DSV = zeros(ns,nt); % S Vol
DBV = zeros(ns,nt); % B Vol
SBR = zeros(ns,nt); % S/B Ratio
SS = zeros(s,nt);
% V = zeros(s,1);
%% Write data to Mat
itick = getitick(si,100,D{1}); % Read the first 100 records to determine time tick.
DP(:,itick) = D{3};
DBV(:,itick) = D{9}+D{10}+D{11}+D{12}+D{13};
DSV(:,itick) = D{19}+D{20}+D{21}+D{22}+D{23};
% add 0.1 to prevent INF value,'.*(DBV(:,itick)~=0)'to zero out those DBV==0 case.
SBR(:,itick) = DSV(:,itick)./(DBV(:,itick)+0.1).*(DBV(:,itick)~=0); 
[~,tmp] = sort(SBR(:,itick),'descend');
SS(:,itick) = tmp(1:s);
stmp = reshape(SS,1,[]);
tmp = stmp(stmp>0);
topm = tabulate(tmp);
topms = sortrows(topm, -3);
V = topms(1:s,1);
%% Main Loop
lt = 0;
while lt < 10000 % Detecting time
    fh = dir([pwd,['\',filename]]);
    t = datevec(fh.date,'dd-mmm-yyyy HH:MM:ss');
    te = etime(t,t0);
    if te > 0 
        t0 = t;
        fh.date
        fileID = fopen(filename);
        C_text = textscan(fileID,formatSpec,nf,'delimiter','\n');
        D = textscan(fileID,'%s %s %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %d %d %d %d %d','delimiter',',');
        fclose(fileID);
        %% Write data to Mat
        itick = getitick(si,100,D{1}); % Read the first 100 records to determine time tick.
        DP(:,itick) = D{3};
        DBV(:,itick) = D{9}+D{10}+D{11}+D{12}+D{13};
        DSV(:,itick) = D{19}+D{20}+D{21}+D{22}+D{23};
        SBR(:,itick) = DSV(:,itick)./(DBV(:,itick)+0.1).*(DBV(:,itick)~=0); 
        [~,tmp] = sort(SBR(:,itick),'descend');
        SS(:,itick) = tmp(1:s);
        for j=1:s 
            D{2}(tmp(j))
        end
        stmp = reshape(SS,1,[]);
        tmp = stmp(stmp>0);
        topm = tabulate(tmp);
        topms = sortrows(topm, -3);
        V = topms(1:s,1);
    else
        pause(10);
        lt = lt + 1;
    end
end
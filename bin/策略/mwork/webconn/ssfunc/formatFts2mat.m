function formatFts2mat(nd)
%% Clean work
% clear; clc; close all;
tic;
%nd = 600; % Extract number of latest daily data 

%% Load All Fts .mat file
dirLoadYahooFts;

%% Extract and Format FTS to 3D Matrix
N  = length(corpList);
j = 1;
dk1 = zeros(N,nd,5); % nd Daily OHLC and Vol.
dk1_date = zeros(N,nd); % Time ticks for dk1
for i=1:N
    Security = cell2mat(corpList_S(i));
    ss=[Security(8:9),Security(1:6)];
    try
        eval(['lastData = fts2mat(',ss,'(end-nd+1:end),1);']);
        lastData = lastData( end:(-1):1, : );
        dk1(i,:,:) = lastData(:,2:6);
        dk1_date(i,:) = lastData(:,1);
    catch
        warning('Security data missing %s. (Loop ID: %d)).',Security,i);
        corpMsList(j)=i;
        j=j+1;
        continue;
    end
end
%´æ´¢MatÎÄ¼þ
fpathname=[pwd, '\ssfunc\', 'dk1.mat'];
save(fpathname, 'dk1','dk1_date'); % Save to Mat file

%% Record Time
toc;
end


    
    
    

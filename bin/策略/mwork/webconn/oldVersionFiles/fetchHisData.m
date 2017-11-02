%% Clean work
tic; clear; clc; close all;
format compact;
load corpList.mat;

N=length(corpList);
%% Connect to Yahoo! 
Connect = yahoo;
load yhfields.mat; % Intrinsic .mat var.
if isconnection(Connect) == 0
    error('Please check network connection.');
end
%% Fields and Date Parameters
Fields = {'Open';'High';'Low';'Close';'Volume'};
ToDate = today;
%datestr(ToDate)
FromDate = today-365*25; % Get all posiible histrical data.
%% Get Data from Yahoo
if isconnection(Connect) == 1
%    for i=1:N
    for i=1001:N
        Security = cell2mat(corpList_S(i));
        try
            %FETCH: Request data from Yahoo! Finance
            stock = fetch(Connect, Security, Fields, FromDate, ToDate);
%           stock = fetch(Connect, Security, Fields);
        catch
            warning('Fail to fetch %s. (Loop ID: %d).',Security,i);
            continue;
        end    
        stock = stock( end:(-1):1, : );    
        stockfts = fints(stock(:,1),stock(:,2:end),Fields,'D',Security);
        % Open High Low Close Volume
%        stockmat = fts2mat(stockfts);
%        date = stockfts.dates;
        
        %´æ´¢MatÎÄ¼þ
        ph=[pwd, '\fdata\'];
        ss=[Security(8:9),Security(1:6)];
        fpathname=[ph, ss, '.mat'];
        ss2=[ss,'=stockfts;'];
        eval(ss2); % Save fts data with a specified variable name.
        save(fpathname, ss); % Save to Mat file
        
        pause(7); % Wait some seconds for IO and net communication.
    end
end
%% Close Yahoo! connection.
close(Connect);
%% Record Time
toc;
        
        
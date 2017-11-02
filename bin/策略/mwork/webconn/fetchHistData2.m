%% Clean work
tic; clear; clc; close all;
% Parameters
T = 0.25; % files generated within T day will not be updated.
dt= 4;   % Wait time in seconds before fetch the next. 

% Import and formatting data
load MWORK_ENV.mat
cd(MWORK_ROOT)
cd .\webconn;
format compact;
load corpList.mat;
fl = dir([pwd,'\fdata\S*.mat']);
flc=struct2cell(fl)';
fl_name=flc(:,1);
fl_time=flc(:,2);
N  = length(corpList);

%% Connect to Yahoo! 
try
    Connect = yahoo;
catch
    Connect = yahoo('http://download.finance.yahoo.com');
end
load yhfields.mat; % Intrinsic .mat var.
if isconnection(Connect) == 0
    error('Please check network connection.');
end
%% Fields and Date Parameters
Fields = {'Open';'High';'Low';'Close';'Volume'};
ToDate = today+1;
%datestr(ToDate)
FromDate = today-365*25;
FirstDate = today-365*25; % Get all posiible histrical data.
%% Counter
j=1; k=1;l=1;
%% Get Data from Yahoo
if isconnection(Connect) == 1
%    for i=1:N
    for i=1:N
        i
        Security = cell2mat(corpList_S(i));
        ss=[Security(8:9),Security(1:6)];
        fpathname=[pwd, '\fdata\', ss, '.mat'];
        % Check if Security .mat file exists.
        [is_m,loc_fl] = ismember([ss,'.mat'],fl_name); 
        if(is_m) % If exists.
            if now-datenum(cell2mat(fl_time(loc_fl))) < T % If the .mat file is generated within T day.
                continue;
            else % Or maybe new data need to be fetched.
                % Load 
                eval(['load ', fpathname]);
                eval(['LastData = fts2mat(',ss,'(end),1);']);
                % Fetch
                try
                    stock = fetch(Connect, Security, Fields, LastData(1), ToDate); % LastData(1) is the date of last record
                    stock = stock((stock(:,end)>0),:); % Remove no trading volume data.
                    if isempty(stock)
                        warning('No trading days %s. (Loop ID: %d, since Date: %s)).',Security,i,datestr(LastData(1)))
                        continue
                    end
                catch
                    warning('Fail to fetch %s. (Loop ID: %d, Date: %s)).',Security,i,datestr(LastData(1)));
                    fetchOneFailID(j)=i;
                    j=j+1;
                continue;
                end
                nday = length(stock(:,1));
                if(max(LastData-stock(end,:))==0) % New fetched data matchs .mat file data
                    if(nday==1) % No new data need to be added into .mat file
                        continue;
                    elseif(nday>1) % Vertically concatenate new fint to .mat file
                        stock = stock( end-1:(-1):1, : );
                        stockfts = fints(stock(:,1),stock(:,2:end),Fields,'D',Security);
                        eval([ss,'= [',ss,';stockfts];']);
                        save(fpathname, ss); % Save to Mat file
                    end
                else % New fetched data doesn't match .mat file data due to Split or Devidend.                    
                    flg = fetchSave(Connect, Security, Fields, FirstDate, ToDate);
                    if flg==0
                         warning('Fail to fetch %s. (Loop ID: %d, Date: %s)).',Security,i,datestr(FirstDate));
                         fetchUpdateFailID(l)=i;
                         l=l+1;
                    end
                    pause(dt); % Wait some seconds for IO and net communication.
                end
            end
        else % If Security .mat file isn't exists, try to fecth...
            flg = fetchSave(Connect, Security, Fields, FirstDate, ToDate);
            if flg == 0
                warning('Fail to fetch %s. (Loop ID: %d).',Security,i);
                fetchAllFailID(k)=i;
                k=k+1;
                continue;
            end
            pause(dt); % Wait some seconds for IO and net communication.
        end
    end
end
%% Close Yahoo! connection.
close(Connect);
%% Record Time
toc;
        
        
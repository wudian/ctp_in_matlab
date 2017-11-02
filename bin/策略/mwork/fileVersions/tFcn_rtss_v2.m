function tFcn_rtss(obj,eventdata,UserData)
%% Version 2.0
% Global Graphic Handles
global fig_h;
global sp_h1;
global ax_h1;
global ax_h2;
global ax_h3;
global line_ax1_h;


%% Initialize variables.
% Callback Parameters
UD2 = get(obj, 'UserData');
filename = UD2.filename;
si = UD2.si;
t0 = UD2.t0;
SS = UD2.SS;
scanTimes = UD2.scanTimes;
scanTimes = scanTimes + 1;
UD2.scanTimes = scanTimes;
s = length(SS(:,1)); % Number of TopN 
% Local Parameters
nt = 240*(60/si) + 1;  % Number of time ticks
% Initialize Graphic Handles
x = 0:nt-1;
y = zeros(1,nt); 
colors={'-r.' '-bx' '-k+' '-ms' '-md' '-cv' '-g' '-b' '-y' '-m' '-c'};
nc = length(colors);
%% File Header Scanning Parameters
formatSpec = '%s';
nf = 1;
%% Dir and File monitoring
fh = dir([pwd,['\',filename]]);
t = datevec(fh.date,'dd-mmm-yyyy HH:MM:ss');
te = etime(t,t0);
if te > 0     
    UD2.t0 = t;
    fh.date;
    fileID = fopen(filename);
    textscan(fileID,formatSpec,nf,'delimiter','\n');
    D = textscan(fileID,'%s %s %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %d %d %d %d %d','delimiter',',');
    fclose(fileID);
    %% Write data to Mat
    itick = getitick(si,100,D{1})-10+scanTimes; % Read the first 100 records to determine time tick.
    VP = D{3};    
    VBV = D{9}+D{10}+D{11}+D{12}+D{13};
    VSV = D{19}+D{20}+D{21}+D{22}+D{23};
    VSBR = VSV./(VBV+0.1).*int32(VBV~=0);     
    %% Sorting
    [~,tmp] = sort(VSBR,'descend');
    SS(:,itick) = tmp(1:s);
    for j=1:s 
        D{2}(tmp(j));
    end
    stmp = reshape(SS,1,[]);
    tmp = stmp(stmp>0);
    topm = tabulate(tmp);
    
    topms = sortrows(topm, -2);
    sbr_topN = topms(1:s,1);
     
     [D{2}(sbr_topN(1)) D{2}(sbr_topN(2)) D{2}(sbr_topN(3))] 
          [D{2}(sbr_topN(4)) D{2}(sbr_topN(5))] 

   
    sbr_topN_count = topms(1:s,2);
    
    %% Wirting back to UserData
    UD2.DP(:,itick) = VP;
    UD2.DSV(:,itick) = VSV;
    UD2.DBV(:,itick) = VBV;
    UD2.SBR(:,itick) = VSBR;
    UD2.SS = SS;
    UD2.sbr_topN = sbr_topN;    
    set(obj, 'UserData', UD2);
    save UD.mat -struct UD2 
    %% Plot
    if scanTimes == 1 % Initial Graphic Obj
        fig_h = figure;
        sp_h1 = subplot(2,2,[1,2]);
        axis([0,nt-1,-0.1,0.1]);grid on; hold on         
        for i=1:min(nc,s)
            plot(x,y,colors{i});
        end
        ax_h1=gca;
        line_ax1_h=get(ax_h1,'Children'); % Get Handles for each Line
        
        subplot(2,2,3);        plot(x,cos(x));        ax_h2=gca;
        subplot(2,2,4);        plot(x,tan(x));        ax_h3=gca;        
        AX_h = get(fig_h,'Children');        
    else
        %% Data for Visualization
        for i = 1:s
           
            [~,c]=find(SS==sbr_topN(i));
            c = min(c);
            for j=1:min(nc,s)
               
                eval(['x',num2str(j),'=x(c:itick);']);
                tmpx = x(c:itick);
                tmpy = UD2.DP(sbr_topN(i),tmpx);
%                tmpy = (tmpy-tmpy(1))/tmpy(1); % Persentage change to the first point
                tmpy(end)
                eval(['x',num2str(j),'=tmpx;'])
                eval(['y',num2str(j),'=tmpy;'])
                eval(['set(line_ax1_h(j),','''XData''',',x', num2str(j),',','''YData''',',y', num2str(j),(');')]) 
                refreshdata(line_ax1_h(j),'caller');
            end
            drawnow;
            
        end
        
    end
end    
%set(obj, 'UserData', UD2);
end







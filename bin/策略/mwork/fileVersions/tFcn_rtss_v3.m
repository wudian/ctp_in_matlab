function tFcn_rtss(obj,eventdata,UserData)
%% Version 3.0 -- Add saving data utility
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
colors={'-r.' '-b' '-k' '-m' '-c' '-g'};
nc = length(colors);
%% File Header Scanning Parameters
formatSpec = '%s';
nf = 1;
%% Dir and File monitoring
%try
    fh = dir([pwd,['\',filename]]);
    t = datevec(fh.date,'dd-mmm-yyyy HH:MM:ss');
    te = etime(t,t0);
    if te > 0     
        UD2.t0 = t;
         fh.date
        fileID = fopen(filename);
        textscan(fileID,formatSpec,nf,'delimiter','\n');
        D = textscan(fileID,'%s %s %f %f %f %f %f %f %d %d %d %d %d %f %f %f %f %f %d %d %d %d %d','delimiter',',');
        fclose(fileID);
        %% Write data to Mat
        itick = getitick(si,100,D{1}); % Read the first 100 records to determine time tick.
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
        sbr_topN_count = topms(1:s,2);

        [D{2}(sbr_topN(1)) D{2}(sbr_topN(2)) D{2}(sbr_topN(3)) D{2}(sbr_topN(4)) D{2}(sbr_topN(5))] 
        [sbr_topN_count(1) sbr_topN_count(2) sbr_topN_count(3) sbr_topN_count(4) sbr_topN_count(5)]

        %% Wirting back to UserData
        UD2.DP(:,itick) = VP;
        UD2.DSV(:,itick) = VSV;
        UD2.DBV(:,itick) = VBV;
        UD2.SBR(:,itick) = VSBR;
        UD2.SS = SS;
        UD2.sbr_topN = sbr_topN; 
        set(obj, 'UserData', UD2);
        %% Save data 
        if itick > nt-1
            SSN = D{2}(UD2.SS(UD2.SS~=0));
            VT = cell2table(D{2}(int32(UD2.sbr_topN)));
            d = cell2mat(D{1}(1));
            dn = d([1:4 6 7 9 10]);
            eval(['save .\rtHistDat\rt',dn,'.mat UD2 SSN'])
            eval(['writetable(VT, ','''.\rtHistDat\VT',dn,'.txt''',')'])
            %save UD.mat -struct UD2 
        end
        %% Plot
        if scanTimes == 1 % Initial Graphic Obj
            fig_h = figure;
            sp_h1 = subplot(2,2,[1,2]);
            %axis([0,nt,-0.1,0.1]);grid on; 
            %axis([0,nt-1,-0.1,100]);grid on; 
            hold on         
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
            for i = 1:min(nc,s)
                [~,c]=find(SS==sbr_topN(i));
                c = min(c);
               % for j=1:min(nc,s)
                eval(['x',num2str(i),'=x(c:itick);']);
                tmpx = x(c:itick);                
                tmpy = UD2.DP(sbr_topN(i),tmpx);
                idx = find(tmpy~=0); % Get rid of zero values
                tmpx = tmpx(idx);
                tmpy = tmpy(idx);
                try
                    tmpy = (tmpy-tmpy(1))/tmpy(1); % Persentage change since recorded                
                    eval(['x',num2str(i),'=tmpx;'])
                    eval(['y',num2str(i),'=tmpy;'])
                    eval(['set(line_ax1_h(i),','''XData''',',x', num2str(i),',','''YData''',',y', num2str(i),(');')]) 
                    refreshdata(line_ax1_h(i),'caller');
                    drawnow;
                catch
                    warning('Waiting for valid output');
                end
               % end
            end

        end
    end    
%set(obj, 'UserData', UD2);
%catch
%   warning('file not found'); 
%end
end







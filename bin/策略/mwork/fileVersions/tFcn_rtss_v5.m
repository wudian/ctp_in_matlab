function tFcn_rtss(obj,eventdata,UserData)
%% Version 3.0 -- Add saving data utility
%% Version 4.0 -- Graphic enhance
%% Version 5.0 -- Fine selection
% Global Graphic Handles
global fig_h1;
global fig_h2;
global sp_h1;
global ax_h1;
global ax_h2;
global ax_h3;
global line_ax1_h;
global sctr_ax2_h;
global text_ax2_h;
global cc;  % Color scaler


%% Initialize variables.
% Callback Parameters
UD2 = get(obj, 'UserData');
filename = UD2.filename;
si = UD2.si;
t0 = UD2.t0;
SSI = UD2.SSI; % Selected Security Index
scanTimes = UD2.scanTimes;
rsb = UD2.rsb;
scanTimes = scanTimes + 1;
UD2.scanTimes = scanTimes;
s = length(SSI(:,1)); % Number of TopN 
% Local Parameters
nt = 240*(60/si) + 1;  % Number of time ticks
% Initialize Graphic Handles
x = 0:nt-1;
y = zeros(1,nt); 
cv_x = zeros(s,1);
cv_y = zeros(s,1);
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
        SName = cell2mat(D{2});
        SName = SName(:,3:end);
        SName = cellstr(SName);
        %% Write data to Mat
        itick = getitick(si,100,D{1}); % Read the first 100 records to determine time tick.
        VP = D{3};    
        VBV = D{9}+D{10}+D{11}+D{12}+D{13};
        VSV = D{19}+D{20}+D{21}+D{22}+D{23};
        VSBR = VSV./(VBV+0.1).*int32(VBV~=0);     
        %% Sorting
        [tmpvr,tmp] = sort(VSBR,'descend');
        %tmp1 = tmp(tmpvr>rsb); % 
        SSI(:,itick) = tmp(1:s);
        %if ~isempty(tmp1)
        %    s1 = min(s,length(tmp1));
            %SSI(:,itick) = tmp(1:s);
        %end
        %for j=1:s 
        %    SName(tmp(j));
        %end
        stmp = reshape(SSI,1,[]);       
        % Modified in Version 5.0.  Adding selection threshold 'rsb'
        tmp = stmp(stmp>rsb); % Old threshold is 0.
        topm = tabulate(tmp);

        topms = sortrows(topm, -2);
        sbr_topN = topms(1:s,1);
        sbr_topN_count = topms(1:s,2);

        [SName(sbr_topN(1)) SName(sbr_topN(2)) SName(sbr_topN(3)) SName(sbr_topN(4)) SName(sbr_topN(5))] 
        [sbr_topN_count(1) sbr_topN_count(2) sbr_topN_count(3) sbr_topN_count(4) sbr_topN_count(5)]

        %% Wirting back to UserData
        UD2.DP(:,itick) = VP;
        UD2.DSV(:,itick) = VSV;
        UD2.DBV(:,itick) = VBV;
        UD2.SBR(:,itick) = VSBR;
        UD2.SSI = SSI;
        UD2.sbr_topN = sbr_topN; 
        set(obj, 'UserData', UD2);
        %% Save data 
        if itick > nt-1
            SSN = SName(UD2.SSI(UD2.SSI~=0));
            VT = cell2table(SName(int32(UD2.sbr_topN)));
            SL = D{2};
            d = cell2mat(D{1}(1));
            dn = d([1:4 6 7 9 10]);
            eval(['save .\rtHistDat\rt',dn,'.mat SL UD2 SSN'])
            eval(['writetable(VT, ','''.\rtHistDat\VT',dn,'.txt''',')'])
            %save UD.mat -struct UD2 
        end
        %% Plot
        if scanTimes == 1 % Initial Graphic Obj
            fig_h1 = figure;
            %sp_h1 = subplot(2,2,[1,2]);
            %axis([0,nt,-0.1,0.1]);grid on; 
            %axis([0,nt-1,-0.1,100]);grid on; 
            grid on; hold on         
            cc=jet(s);
            for i=1:s
                plot(x,y,'--','color', cc(mod(i,s)+1, :));
                plot(x,y,'o','color', cc(mod(i,s)+1, :));
            end
            ax_h1=gca;
            % Get Handles for each Line
            line_ax1_h = get(ax_h1,'Children'); 
            %set(line_ax1_h(1:2:end),'Marker','.');
            %set(line_ax1_h(2:2:end),'Marker','*');

            %subplot(2,2,3);        
            fig_h2 = figure;
            grid on; hold on
            scatter(cv_x,cv_y,sbr_topN_count*10,sbr_topN_count);       
            ax_h2=gca;
            % Get Handles for scatter points
            sctr_ax2_h = get(ax_h2,'Children'); 
            text(cv_x, cv_y,SName(sbr_topN),...
                    'horizontal','left', 'vertical','bottom');
            text_ax2_h = findobj(ax_h2,'Type','text');
                
            
            %subplot(2,2,4);        plot(x,tan(x));        ax_h3=gca;        
            %AX_h = get(fig_h1,'Children');        
        else
            %% Data for Visualization
            tmp_name = SName(sbr_topN);
            for i = 1:s
                [~,c]=find(SSI==sbr_topN(i));
                c = min(c);
                eval(['x',num2str(i),'=x(c:itick);']);
                tmpx = x(c:itick);                
                tmpy = UD2.DP(sbr_topN(i),tmpx);
                idx = find(tmpy~=0); % Get rid of zero values
                tmpx = tmpx(idx);
                tmpy = tmpy(idx);
                tmpy2 = UD2.SBR(sbr_topN(i),tmpx);
                idx2  = find(tmpy2>rsb);
                tmpx2 = tmpx(idx2);
                tmpy2 = tmpy(idx2);
                try
                    cv_y(i) = std(tmpy)/mean(tmpy); % Coefficient of Var
                    tmp_p = tmpy(1);
                    tmpy = (tmpy-tmp_p)/tmp_p; % Persentage change
                    tmpy2 = (tmpy2-tmp_p)/tmp_p; % same for marker plot
                    eval(['x',num2str(i),'=tmpx;'])
                    eval(['y',num2str(i),'=tmpy;'])
                                        
                    eval(['xx',num2str(i),'=tmpx2;'])
                    eval(['yy',num2str(i),'=tmpy2;'])  
                    
                    eval(['set(line_ax1_h(2*i),',...p
                        '''XData''',',x', num2str(i),...
                        ',','''YData''',',y', num2str(i),(');')])
                    eval(['set(line_ax1_h(2*i-1),',...
                        '''XData''',',xx', num2str(i),...
                        ',','''YData''',',yy', num2str(i),(');')]) 
                    
                    refreshdata(line_ax1_h(2*i),'caller');                   
                    refreshdata(line_ax1_h(2*i-1),'caller');     
                    drawnow
                    cv_x(i) = tmpy(end);  % Price change                    
                catch
                    warning('Waiting for refreshing price data');
                end
               
            end
            legend1=legend(ax_h1,line_ax1_h(2:2:end),tmp_name,-1);
            set(legend1,'EdgeColor','white');
            try
%                 set(sctr_ax2_h,'XData',cv_x,'YData',cv_y,'SizeData',sbr_topN_count*15,'color',sbr_topN_count*5);
                scatter(ax_h2,cv_x,cv_y,sbr_topN_count*15,sbr_topN_count);
                %axis equal;
                
%                refreshdata(sctr_ax2_h,'caller');
%                 text(ax_h2,cv_x, cv_y,SName(sbr_topN), 'horizontal','left', 'vertical','bottom');
                figure(fig_h2);
                hold on
                 lscatter(cv_x, cv_y,SName(sbr_topN),'MissingLabel','?', ...
                     'TextColor','b','FontSize',8);
                grid on; hold off
%                drawnow;
            catch
                warning('Waiting for refreshing Coefficient of Variation');
            end
        end
    end    
%set(obj, 'UserData', UD2);
%catch
%   warning('file not found'); 
%end
end







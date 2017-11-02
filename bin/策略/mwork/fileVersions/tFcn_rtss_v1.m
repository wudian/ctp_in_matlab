function tFcn_rtss(obj,eventdata,UserData)
%% Initialize variables.
UD2 = get(obj, 'UserData');
filename = UD2.filename;
si = UD2.si;
t0 = UD2.t0;
SS = UD2.SS;
callTimes = UD2.callTimes;
callTimes = callTimes + 1;
UD2.callTimes = callTimes;
s = length(SS(:,1));
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
    itick = getitick(si,100,D{1}); % Read the first 100 records to determine time tick.
    VP = D{3};    
    VBV = D{9}+D{10}+D{11}+D{12}+D{13};
    VSV = D{19}+D{20}+D{21}+D{22}+D{23};
    VSBR = VSV./(VBV+0.1).*int32(VBV~=0); 
    
    %% Sorting
    [~,tmp] = sort(VSBR,'descend');
    SS(:,itick) = tmp(1:s);
    %for j=1:s 
    %    D{2}(tmp(j))
    %end
    stmp = reshape(SS,1,[]);
    tmp = stmp(stmp>0);
    topm = tabulate(tmp);
    
    topms = sortrows(topm, -3);
    sbr_topN = topms(1:s,1);
    %% Wirting back to UserData
    UD2.DP(:,itick) = VP;
    UD2.DSV(:,itick) = VSV;
    UD2.DBV(:,itick) = VBV;
    UD2.SBR(:,itick) = VSBR;
    UD2.SS = SS;
    UD2.sbr_topN = sbr_topN;    
    set(obj, 'UserData', UD2);
    save UD.mat -struct UD2 
end    
%set(obj, 'UserData', UD2);
end







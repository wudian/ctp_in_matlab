function SS_fts = getRtFts(Sname)
%% formatRt2fts

%% Clean work
%tic; clear; clc; close all;
cd F:\mwork\
fl = dir([pwd,'\rtHistDat\rt*.mat']);

for i = 1 : length(fl)
    eval(['load ' fl(i).name])
    fl(i).name
    si = UD2.si;
    max_tn = length(UD2.DP(1,:));
    dn =datenum([UD2.t0(1) UD2.t0(2) UD2.t0(3)]);
    if exist('SL','var')
        [ism,iSS] = ismember(Sname,SL);
    else
        continue
    end
    if ism==0
        %warning('%s not found matched data', Sname);
        continue
    end
    valid_tn = find(UD2.DP(iSS,:)>0);
    max_vtn = length(valid_tn);
    %% Construct fints
    tn = tradTimeFloat(si,max_tn,valid_tn);
    dt = dn+tn;  % Date and Time Vector
    prc = UD2.DP(iSS,valid_tn);
    dsv = UD2.DSV(iSS,valid_tn);
    dbv = UD2.DBV(iSS,valid_tn);
    dt = dt';
    prc = prc';
    dsv = dsv';
    dbv = dbv';
    ts_tmp = fints(dt,[prc,dsv,dbv],[{'price'},{'saleVol'},{'buyVol'}]);  
    if exist('SS_fts','var')
        SS_fts = [SS_fts;ts_tmp];
    else
        SS_fts = ts_tmp;
    end
    clear UD SSN UD2 SL ts_tmp
end
if ~exist('SS_fts','var')
        SS_fts = 0;
        warning('%s: not found matched data', Sname);
end
end

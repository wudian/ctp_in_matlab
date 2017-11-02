function  [SigMat,J] = ssVp( kData,kDate,cond,percent,nD,Smod,Prnt )
%% Select  Volume Pattern Signals
%   INPUT
%   kData: formatted price data [OHLC and Vol] for all securities.
%          Defination:  kData(Ns,Nt,OHLCVs)
%   cond : if 1, ">"; if -1, "<"
%   percent:  volumn threshold.  
%   nD   : Number of days
%   Smod : if 1, latest selection; if 0, return all signal in history.
%   Prnt : if 1, print selected Security Code and NO of selections.
%   OUTPUT
%   SigMat : Logical Index of Selected Security Code in sName
%            First column, the latest day; END column, earliest.
%   J    : if Smod = 1, return number of selection, if Smod = 0, return
%          B/S Signal Matrix for back testing. 
%%
%   Example 1:  Seaching in all history data
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J]=ssVp(dk1,dk1_date,1,0.3,4,0,0);
%
%   Example 2:   Seaching for the latest signals
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J]=ssVp(dk1,dk1_date,1,0.3,4,1,0);
%           corpList_S(SigMat)
% *********************************************************************

%load corpList.mat;
%[isbl,loc] = ismember(sName,spIn);
%kData = kData(isbl,:,:);
NDAY = length(kData(1,:,1));
% J = 1; % Number of selection
if Smod == 1             
    A = kData(:,1:nD,5);     % Vol series of 'TODAY'
    B = kData(:,2:nD+1,5);   % Vol series of 'YESTERDAY'
    if cond == 1
        C = (A>B*(1+percent));               % CONDITION
    elseif cond == -1
        C = (A<B*(1-percent));
    end
    J = sCount(C,nD);
%    idx_sig = loc(J==nD);
    idx_sig = (J==nD);
    J = sum(idx_sig);
    %SS = corpList_T(idx_sig);
%    corpList_T(idx_sig)
    SigMat = idx_sig;
    
    % *******  Remove signal occur before yesterday  ********
    tod = max(kDate(1:10,1));                   % Latest date
    dt = (tod - kDate(:,1))>2;
    SigMat(dt) = false;
    % *******************************************************
    
    if(Prnt==1 && J==0) 
        fprintf('ssVp: %s: No Selection!\n',datestr(tod));
    elseif (Prnt==1 && J>0)
        fprintf('%s: %d selcted in ssVp(%d).\n',datestr(tod), J,nD);
    end

elseif Smod == 0
    NDAY = length(kData(1,:,1));
    SigMat = false(size(kData(:,:,1)));
    for i = 1 : NDAY - nD -1  % Generate Signal Matrix for history data
        kD = kData(:,i:nD+i,:);
        kDt = kDate(:,i:nD+i);
        [SigVec,J] = ssVp(kD,kDt,cond,percent,nD,1,0);
        SigMat(:,i) = SigVec;        
    end
    J = sum(sum(SigMat));    
end

end


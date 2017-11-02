function  [SigMat,J] = ssNp( kData,kDate,nD,percent,Smod,Prnt)
%Select those with N patten in price curve
%   INPUT
%   kData: formatted price data [OHLC and Vol] for all securities.
%          Defination:  kData(Ns,Nt,OHLCVs)
%   sName: Security name of kData corresponding to kData.
%   nD   : Max N partten window (price tick)
%   percent:  threshold. this close to the target price 
%   Smod : if 1, latest selection; if 0, return all signal in history.
%   Prnt : if 1, print selected Security Code and NO of selections.
%   OUTPUT
%   SigMat : Logical Index of Selected Security Code in sName
%            First column, the latest day; END column, earliest.
%   J    : if Smod = 1, return number of selection, if Smod = 0, return
%          B/S Signal Matrix for back testing. 
%
%   Example 1:  Seaching in all history data
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J]=ssNp(dk1,dk1_date,6,0.03,0,0);
%
%   Example 2:   Seaching for the latest signals
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J]=ssNp(dk1,dk1_date,10,0.03,1,0);
%           corpList_S(SigMat)
% *********************************************************************

%load corpList.mat;
%N = length(kData(:,1,1));    % No of Securities in kData
%SS = cell(1);
if Smod == 1  
    SigMat = false(size(kData(:,1,1)));  % Logical Signal Vector
    A = kData(:,1:nD,4);     % Close series of TODAY
    B = kData(:,2:nD+1,4);   % Closes of YESTERDAY
    C = (A>B*1.09);               % Condition
    [aa1,bb1]=find(C==1);
    sub1=[aa1 bb1];
    % If more than one signal, get the 'earliest'
    [D, ia1, ic1] = unique(aa1,'legacy'); 
    D = sub1(ia1,:);
    subidx = sub2ind(size(C),D(:,1),D(:,2));
    E1 = A(D(:,1),1)<B(subidx)*(1+percent);
    E2 = A(D(:,1),1)>B(subidx)*(1-percent);
    indind = E1 & E2;
    indind = D(indind,1);
    SigMat(indind') = true;
%    SS = sName(SigMat)
    J = sum(SigMat);
    
    % *******  Remove signal occur before yesterday  ********
    tod = max(kDate(1:10,1));                   % Latest date
    dt = (tod - kDate(:,1))>2;
    SigMat(dt) = false;
    % *******************************************************
    
    if(Prnt==1 && J==0) 
        fprintf('ssNp: %s: No Selection!\n',datestr(tod));
    elseif (Prnt==1 && J>0)
        fprintf('%s: %d selcted in SSNP(%d).\n',datestr(tod), J,nD);
    end
    
elseif Smod == 0
    NDAY = length(kData(1,:,1));
    SigMat = false(size(kData(:,:,1)));
    for i = 1 : NDAY - nD -1  % Generate Signal Matrix for history data
        kD = kData(:,i:nD+i,:);
        kDt = kDate(:,i:nD+i);
        [SigVec,J] = ssNp( kD,kDt,nD,percent,1,0);
        SigMat(:,i) = SigVec;        
    end
    J = sum(sum(SigMat));    
end

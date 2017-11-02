function  [SigMat,J] = ssRb( kData,kDate,nD,nW,Smod,Prnt)
%Select those with N patten in price curve
%   INPUT
%   kData: formatted price data [OHLC and Vol] for all securities.
%          Defination:  kData(Ns,Nt,OHLCVs)
%   nD   : Maximun incessant days of Low > smooth(Close,Short_MA)
%   nW   : Signal time window (signal valid in the latest N days)
%          This parameter used only when Smod = 1.
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
%           [SigMat,J]=ssRb(dk1,dk1_date,18,1,0,0);
%
%   Example 2:   Seaching for the latest signals happened within nW days
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J]=ssRb(dk1,dk1_date,18,10,1,0);
%           corpList_S(SigMat)
% *********************************************************************

% ********************** Technical Parameters *************************
            Short_MA = 12; % Short Moving Average Parameter
            %Long_MA  = 50; % Long Moving Average Parameter
% *********************************************************************

%load corpList.mat;
%N = length(kData(:,1,1));    % No of Securities in kData
%SS = cell(1);
if Smod == 1  
    %SigMat = false(size(kData(:,1,1)));  % Logical Signal Vector
    A = kData(:,1:2*nD+nW,3);     % Low of Kdata
    B = kData(:,1:2*nD+nW,4);   % Close of Kdata
    B = fliplr(B);
    MA = tsmovavg(B, 'e', Short_MA,2);  % Moving average of Close of Kdata
    MA = fliplr(MA);
    C = (A-MA>0.01);               % Condition
    J = zeros(length(A(:,1)),nW);
    for i =1 : nW
        J(:,i) = sCount(C,i,nD+i-1);
    end
    idx_sig = (J==nD);    
    SigMat = logical(sCount(idx_sig,nW));
    J = sum(SigMat);
    
    % *******  Remove signal occur before yesterday  ********
    tod = max(kDate(1:10,1));                   % Latest date
    dt = (tod - kDate(:,1))>2;
    SigMat(dt) = false;
    % *******************************************************
        
    if(Prnt==1 && J==0) 
        fprintf('ssRb: %s: No Selection!\n',datestr(tod));
    elseif (Prnt==1 && J>0)
        fprintf('%s: %d selcted in SSRB(%d).\n',datestr(tod), J,nD);
    end
    
elseif Smod == 0
    NDAY = length(kData(1,:,1));
    SigMat = false(size(kData(:,:,1)));     
    
    for i = 1 : NDAY - 2*nD-nW -1  % Generate Signal Matrix for history data
        kD = kData(:,i:nD+i,:);
        kDt = kDate(:,i:nD+i);
        [SigVec,J] = ssRb( kD,kDt,nD,1,1,0);
        SigMat(:,i) = SigVec;        
    end
    
    J = sum(sum(SigMat));    
end

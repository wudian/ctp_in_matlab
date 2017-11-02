function [secSigDate, SAP] = CandSig( S1,S2, ConnectionMode, sigShft, ...
                                kData, kDate,corpList_S,iOHLC, nD )

% Plot Fan Chart and Return Signal Dates for Candle Pattern SigMat  
%   INPUT
%   S1     : First Signal Matrex
%   S2     : Second Signal Matrex
%   ConnectionMode:  1, Sigle; 2, Tadem  3, Parallel
%   sigShft: Signal time shift, 0, exec when signal occurs; n, for n days
%               after signal occuring days
%   kData  : formatted price data [OHLC and Vol] for all securities.
%            Defination:  kData(Ns,Nt,OHLCVs)
%   kDate  : formatted date data in correspond with kData
%   corpList_S: Security Name List
%   iOHLC  : 1, Open; 2, High; 3, Low; 4, Close
%   nD     : Range of days for evaluation
%   OUTPUT
%   secSigDate: Security Name and date of Signals 
%   Example:
% *********************************************************************
%           load CandlePatern.mat
%           [secSigDate, SAP] = CandSig( SigMat(:,:,IS1(1,2)),[],...
%                               1, 1,dk1, dk1_date,corpList_S,1, 5 );
% *********************************************************************

if isempty(S2) || ConnectionMode == 1
    S = S1;
elseif ConnectionMode == 2
    S=false(size(S2)); S(:,1:end-1)=S2(:,2:end);S(:,end)=false;
    S = S1 & S;
elseif ConnectionMode == 3
    S = S1 & S2;
end

% Time Shift Signals
S = circshift(S,[0,-1*sigShft]);  
S(:,end-sigShft:end) = false;

if sum(sum(S)) == 0
    warning('No valid signal');
    secSigDate = [];
    return
end    

%% Plot SigFan
try
    [~,~,SAP] = sigFan( kData, S, iOHLC, nD, 1 );
catch
    [FanMat,R,SAP] = sigFan( kData, S, iOHLC, nD, 1 );
end

%% Return Readable Signal Information
secSigDate = sigDate(S,kDate,corpList_S,0);

end





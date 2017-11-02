function [FanMat,R,SAP] = sigFan( kData, SigMat, iOHLC, nD, flg_p )
% Plot Fan Chart for SigMat  
%   INPUT
%   kData  : formatted price data [OHLC and Vol] for all securities.
%            Defination:  kData(Ns,Nt,OHLCVs)
%   SigMat : Logical Index of Selected Security Code in kData
%   iOHLC  : 1, Open; 2, High; 3, Low; 4, Close
%   nD     : number of days
%   flg_p  : Plotting control flag
%
%   Example:
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [S,J]=ssSd(dk1,dk1_date,-1,7,0,0);
%           [FM,R,SAP] = sigFan( dk1, S, 4, 10, 1 );
% *********************************************************************

m = length(kData(:,1,1));
n = length(kData(1,:,1));
% Remove latest signals which have no enough price data to plot
SigMat(:,1:nD+1) = false; 
sigind = find(SigMat==1);
if isempty(sigind)
    warning('No valid signal')
    return
end
[subi,subj] = ind2sub(size(SigMat),sigind);
subij = [subi,subj];
Csubij = mat2cell(subij,ones(size(subi)),2);
K = kData(:,:,iOHLC);
CK = mat2cell(K,ones(m,1),n ); % Convert to Cell

CP = cellfun(...
    @(Csubij) CK{Csubij(1)}(Csubij(2):-1:Csubij(2)-nD),...
    Csubij,'UniformOutput', false);
P = cell2mat(CP);
% Remove unreasonable data
Q = abs(P(:,2:end)-P(:,1:end-1))./P(:,2:end)>0.12;
Q = logical(sum(Q,2));
% Calculate price change since signals occur
P = P./repmat(P(:,1),1,nD+1); 
PP = [subij(:,2) P]; % [SignalTime, PriceVector]
P = P(~Q,:);
PP = PP(~Q,:);
% Remove rows containing Nan.
P(isnan(P(:,2)),:)=[]; 
PP(isnan(PP(:,2)),:)=[]; 

P1 = P(P(:,end)>1,:);
P2 = P(P(:,end)<1,:);
FanMat = P;

tt = unique(PP(:,1));
nt = numel(tt); % Number of Days having signal
PT = zeros(nt,nD+2);
for i=1:nt
    tsubi = PP(:,1)==tt(i);
    if sum(tsubi) == 1
        PT(i,:) = PP(tsubi,:);
    else
        PT(i,:) = mean(PP(tsubi,:));
    end
end
R = [PT(:,1), mean(PT(:,3:end),2)];
for i=1:nt
    R(i,3) = log(prod(R(1:i,2)));
end
PTS = [PT(:,1),R(:,2)-1];
objprc = mean(PTS(:,2));

%% Simple Algorithm Performance
SAP = struct ('AlgoName',[],'NumOfDays',[],...
                           'NumOfTrades',[],...
                           'Simple_average',[],...
                           'Time_average',[],...
                           'Log_accumul_ratio',[],...
                           'Simple_win_rate',[],...
                           'Time_win_rate',[],...
                           'Best_Exit_Day',[]);
mn1 = mean(P); 

SAP.NumOfDays = nt;                       
SAP.NumOfTrades = numel(subi);
SAP.Simple_average = mean(mean(P));
SAP.Time_average = mean(mean(PT(:,2:end)));
SAP.Log_accumul_ratio = R(end,3);
SAP.Simple_win_rate = sum(sum(P(:,2:end)>1))/(numel(P)-numel(P(:,1)));
SAP.Time_win_rate = sum(sum(PT(:,3:end)>1))/(numel(PT)-2*numel(PT(:,1)));
SAP.Best_Exit_Day = find( mn1==max(mn1) );
                       
%% Plot
if flg_p
   figure;
   title('SSNP')
   subplot(4,2,1);
   plot([1:nD+1],P1,'r-'),grid on
   subplot(4,2,2);
   plot([1:nD+1],P2,'b-'),grid on
   subplot(4,2,3);  
   mn2 = mean(PT(:,2:end));
   plot([1:nD+1],mn1,'go-',[1:nD+1],mn2,'ro--'),grid on 
   %plot([1:nD+1],mn2,'r')
   subplot(4,2,4);
   histfit(P(:,end),200),grid on
   subplot(4,2,[5 6]);   
   for i=1:nt
    t = PT(i,1)-nD : PT(i,1);
    if PT(i,end)<=1
        plot(t,PT(i,end:-1:2)),hold on % Time elapse from left to right
    %plotyy(t,PT(i,end:-1:2),i,sum(SigMat(:,i)),@bar),hold on 
    elseif PT(i,end)>1
        plot(t,PT(i,end:-1:2),'r'),hold on
    end
   end
   axis([0 n 0.2 3]);
   grid on
   subplot(4,2,[7 8]);
   %bar(fliplr(sum(SigMat))),grid on
   nv = sum(SigMat);
   maxy = ceil(1.1*max(sum(SigMat)));
   bar(nv);
   axis([0 n -1 maxy]),grid on
   
   figure;
   subplot(2,2,[1 2]);
   bar(PTS(:,1),PTS(:,2)),hold on
   plot(PTS(:,1),objprc*ones(size(PTS(:,1))),'r');
   subplot(2,2,3);
   bar(sort(PTS(:,2))),grid on;
   subplot(2,2,4);
   histfit(PTS(:,2)),grid on;   
   
   
end

end


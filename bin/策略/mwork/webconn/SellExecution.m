function [SelSub, BuySub] = SellExecution(...
    kData, SigMat, iOHLC, nD, fixStop, trailStop1, trailStop2 )
% General selling signal operation
%   INPUT
%   kData  : formatted price data [OHLC and Vol] for all securities.
%            Defination:  kData(Ns,Nt,OHLCVs)
%   SigMat : Logical Index of Selected Security Code in kData
%            First column, the latest day; END column, earliest.
%   iOHLC  : 1, Open; 2, High; 3, Low; 4, Close
%   nD     : maximum number of days before exit, if 0, no operation.
%   fixStop: fix stop loss, if 0, no operation.
%   trailStop1  : trailing stop loss with fixed percentage of retracement.
%                 e.g, 0.05, exit when price fall down 5% since highest
%                 if 0, no operation.
%   trailStop2  : trailing stop loss with float percentage of retracement.
%                 e.g, 0.7, exit when price fall down to 70% level between 
%                 entry and highest price, if 0, no operation.
%   OUTPUT
%   SelSub : ij index and exit type of sell signals
%            Sell signal types. 1, exit after nD days; 2, fixStop; 
%            3, fixed trailing stop; 4, retracement measure by entry price.
%   BuySub : ij index of buy signals
%
%   Example:
% *********************************************************************
%           load corpList.mat
%           load dk1.mat
%           [SigMat,J] = ssNp(dk1,6,0.03,0,0);
%     [SelSub, BuySub] = SellExecution(kData,SigMat,4, 20, 0.05,0.1,0.7 );
% *********************************************************************

[m n] = size(SigMat);
K = kData(:,:,iOHLC);
%enter_price = K(SigMat);

sig_idx = find(SigMat==1);
[sig_subi, sig_subj] = ind2sub(size(SigMat),sig_idx);
sig_sub = [sig_subi, sig_subj];
sig_sub(sig_sub(:,2)==1,:) = []; % Remove signal of 'Today'
sig_subi = sig_sub(:,1);
sig_subj = sig_sub(:,2);

% Transform logical B-signals and B-price to sub-index vector 
linearInd1 = sub2ind(size(SigMat),sig_subi, sig_subj);
BuySub = [sig_subi,sig_subj,K(linearInd1)];

ns = numel(sig_subi);  % No of valid B-signal
sig_subj1 = zeros(size(sig_subj));
sig_subj2 = zeros(size(sig_subj));
sig_subj3 = zeros(size(sig_subj));
sig_subj4 = zeros(size(sig_subj));
if ns>0
    if nD>0 % When maximum holding day nD is set.
        sig_subj1 = sig_subj - nD;
        sig_subj1(sig_subj1<0) = 0; 
    end

    if fixStop>0 % When fixStop is set.
        for i=1:ns % Loop for every B signal
            P = K(sig_subi(i),1:sig_subj(i));
            enter_price = P(end);
            if (isempty(P) || max(P)==0)
                continue;
            end
            tmp = find(P<=enter_price*(1-fixStop), 1, 'last' );
            if isempty(tmp)
                continue;
            else
                sig_subj2(i) = tmp;
            end
        end
    end

    if trailStop1>0 % When trailStop1 is set.
        for i=1:ns % Loop for every B signal
            P = K(sig_subi(i),1:sig_subj(i));
            enter_price = P(end);
            if (isempty(P) || max(P)==0)
                continue;
            end
            max_prc = enter_price;
            JJ = sig_subj(i);
            for j = sig_subj(i)-1:-1:1
                if P(j) > max_prc
                    max_prc = P(j);
                    JJ = j;
                end
                tmp = find(...
                    P(1:JJ)<=max_prc*(1-trailStop1), 1, 'last' );
                if isempty(tmp)
                    sig_subj3(i) = 1;
                else
                    sig_subj3(i) = tmp;
                    break;
                end
            end
        end
    end

    if trailStop2>0 % When trailStop1 is set.
        for i=1:ns % Loop for every B signal
            P = K(sig_subi(i),1:sig_subj(i));
            enter_price = P(end);
            if (isempty(P) || max(P)==0)
                continue;
            end
            max_prc = enter_price;
            JJ = sig_subj(i);
            for j = sig_subj(i)-1:-1:1
                if P(j) > max_prc
                    max_prc = P(j);
                    JJ = j;
                end
                tmp = find( P(1:JJ)<=...
                    enter_price+(max_prc-enter_price)*trailStop1,...
                    1, 'last' );
                if isempty(tmp)
                    sig_subj4(i) = 1;
                else
                    sig_subj4(i) = tmp;
                    break;
                end
            end
        end
    end

    sig_subj = [sig_subj1,sig_subj2,sig_subj3,sig_subj4];    
    [sig_subj, sell_type] = max(sig_subj,[],2);
    idx = sig_subj>0;
    sig_subi = sig_subi(idx);
    sig_subj = sig_subj(idx);
    sell_type = sell_type(idx);
    linearInd2 = sub2ind(size(SigMat),sig_subi, sig_subj);
    SelSub = [sig_subi, sig_subj, sell_type, K(linearInd2)];
    BuySub = BuySub(idx,:);
%     
%     SelSub = false(size(SigMat));
%     SelSub(linearInd) = true;
%     TypeMat = zeros(size(SigMat));
%     TypeMat(linearInd) = sell_type;
else
    warning('No valid Buy Signal.');
    SelSub = [];
end

end


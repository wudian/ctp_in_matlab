function [CSAP,C,IM,RR] = matGen2(SigMat1,SigMat2,kData,evnd,mSa,mSwr,mTrd,Pflg)
%% Generate Child-Signal from SigMat1 & SigMat2 and return
%% CSAP struct array by function sigFan
%   INPUT
%   SigMat1, SigMat2  :  Parent signal matrices
%   kData: formatted price data [OHLC and Vol] for all securities.
%          Defination:  kData(Ns,Nt,OHLCVs)
%   evnd : evaluating time priod, default 5 days for short term method.
%   mSa  : return information of signals with abs(SimpleAverage-1)>mSa
%   mSwr : return information of signals with abs(SimpleWinRate-0.5)>mTwr  
%   mTrd : return information of signals with NO of signals > mTrd 
%   Pflg : if 1, plot SigFan; 
%   OUTPUT
%   CSAP : Struct of Simple Algorithm Performance defined in sigFan.m
%   C    : all combination of the indix of Child-signal-matrix
%   IM   : Information matrix 
%   RR   : Simple and Log-Cumulative Rate of Return for selected
%          Signal Matrix
% ----------   SSMat  : Selected Signal Matrix Cube
%%
%   Example 1:  Seaching in all history data
% *********************************************************************
% SM2=SigMat; SM2(:,1:end-1,:)=SigMat(:,2:end,:);SM2(:,end,:)=false;
% [CSAP2,C2,IM,RR,SSM] = matGen2(SigMat,SM2,dk1,4,0.008,0.0,50,0);
% sigFan( dk1, SSM(:,:,1), 4, 6, 1 );
% *********************************************************************


sz1 = size(SigMat1);
sz2 = size(SigMat2);
if numel(sz1)==2
    nf1 = 1;
else
    nf1 = sz1(3);
end
if numel(sz2)==2
    nf2 = 1;
else
    nf2 = sz2(3);
end

l = 0; k = 0; % Individual IDX
IM = zeros(1,8);
%SSMat = zeros([sz1,sz2]);
for i = 1:nf1
    %i
    for j = 1:nf2
        if numel(sz1)==3
            m1 = sum(sum(SigMat1(:,:,i)));
        elseif numel(sz1)==2
            m1 = sum(sum(SigMat1));
        end
        if numel(sz2)==3
            m2 = sum(sum(SigMat2(:,:,i)));
        elseif numel(sz2)==2
            m2 = sum(sum(SigMat2));
        end
        mm = min([m1,m2]);
        if numel(sz2)==3
            SM = SigMat1(:,:,i) & SigMat2(:,:,j); 
        elseif numel(sz2)==2
            SM = SigMat1(:,:,i) & SigMat2; 
        end
        
        minsum = sum(sum(SM));

       if (0<minsum && minsum<mm) || (0<minsum && m2 == sz2(1)*sz2(2)) 
           try
               l = l + 1;
               [FanMat,RR{l},CSAP(l)] = sigFan( kData, SM, 4, evnd, Pflg );
               CSAP(l).AlgoName = ['I',num2str(i),'I',num2str(j)];
                CSAP(l)
                C{l} = [i,j];
                %% Selection
                if( abs(CSAP(l).Simple_average - 1) >= mSa &&...
                    abs(CSAP(l).Simple_win_rate - 0.5) >= mSwr &&...
                    CSAP(l).NumOfTrades > mTrd )
                    k = k + 1;
                    IM(k,:) = [l,i,j,CSAP(l).Simple_average,...
                        CSAP(l).Simple_win_rate,...
                        CSAP(l).Log_accumul_ratio,...
                        CSAP(l).NumOfDays,...
                        CSAP(l).NumOfTrades ];
                    %SSMat(:,k) = SM;
                end
           catch
               continue
           end
       end  
    end
end
end
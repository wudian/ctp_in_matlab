function [Sig,other] = sigKD(Open, High, Low, Close, Date,N,M1,M2,upper,bottom)


RSV=(Close-llow(Low,N))./(hhigh(High,N)-llow(Low,N))*100;
K=sma(RSV,M1);
D=sma(K,M2);

% original program
Sig1=Cross2(K,D).*(K<bottom).*(D<bottom); %BPK 
Sig2=Cross2(D,K).*(K>upper).*(D>upper); %SPK 
Sig3=Sig2;
Sig4=Sig1;


Sig=[Sig1,Sig2,Sig3,Sig4];
other=[K,D];

end
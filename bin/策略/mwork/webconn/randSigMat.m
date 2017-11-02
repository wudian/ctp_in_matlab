function rSigMat = randSigMat( SigMat )
%randSigMat Generate 3 kind of random signals base on SigMat
%   INPUT
%   SigMat : [m,n] Logical Index of Selected Security Code in kData
%   OUTPUT
%   rSigMat: [m,n,3] Logical Index matrix£º
%            [m,n,1], random signal in both Col(time) and Row(Secrities) DIM;
%            [m,n,2], shuffle in Row and keep Col feature. (Timing Signal)
%            [m,n,3], shuffle in Col and keep Row feature. (Secrities Signal)

[m, n] = size(SigMat);
mn = m*n;
sm = sum(SigMat,2);
sn = sum(SigMat);
nss = sum(sn);
R1 = false([m n]);
R2 = false([m n]);
R3 = false([m n]);
rSigMat = false([m n 3]);


ijr1 = randperm(mn,nss);
R1(ijr1) = true;
for j=1:n
    ir2 = randperm(m,sn(j));
    R2(ir2,j) = true;
end
for i=1:m
    jr3 = randperm(n,sm(i));
    R3(i,jr3) = true;
end
rSigMat(:,:,1) = R1;
rSigMat(:,:,2) = R2;
rSigMat(:,:,3) = R3;
end


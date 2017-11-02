function secSigDate = sigDate(SigMat,kDate,corpList_S,sortMod)
%% Return the Date string matrix for given SigMat
% sortMod: 0, return latest first; 1, return by stock by stock

sz = size(SigMat);
MatDate = zeros(sz);
if numel(sz)==2
    MatDate(SigMat) = kDate(SigMat);
% elseif numel(sz)==3    
%     for i=1:sz(3)
%         a = zeros(sz(1:2));
%         a(SigMat(:,:,i)) = kDate(SigMat(:,:,i));
%         MatDate(:,:,i) = a;
end
    
[ii,ij]=find(MatDate>0);
if sortMod==1
    [E,index] = sortrows([ii,ij], 1);
    ii = E(:,1);
    ij = E(:,2);
end
for i=1:numel(ii)
    secSigDate{i} = [datestr(MatDate(ii(i),ij(i))),' ',cell2mat(corpList_S(ii(i)))];
end
secSigDate = secSigDate';
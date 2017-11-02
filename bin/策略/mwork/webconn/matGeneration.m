function [CSAP,C] = matGeneration(SigMat,kData,nG,evnd, Pflg2)

sz = size(SigMat);
if numel(sz)==2
    warning('Invalid input');
    return
else
    nf = sz(3);
end

v = 1 : nf;
% for i = 1 : nf-2  % All Generation
%     C{i} = nchoosek(v,i+1);
% end
for i = 1 : nG  % Only nG Generation
    C{i} = nchoosek(v,i+1);
end


% Here need to add algo reduce individuals with conflict genes

for i = 1 : nG  % Loop for Generation
    [m1,n1] = size(C{i});
    l = 0; % Individual IDX
    for j = 1 : m1  % Loop for Individual        
       SM = SigMat(:,:,C{i}(j,1));
       minsum = sum(sum(SM));
       flg = 1;
       for k = 2 : n1  % Loop for Gene
           SM = SM & SigMat(:,:,C{i}(j,k));     
           mm = sum(sum(SM));
           if mm == 0 % Empty individual
               flg = 0;
               break;           
           elseif mm == minsum % Individual with duplicate gene 
               flg = 0;
               break;
           else
               minsum = mm;
           end           
       end 
       if flg == 1
           try
               l = l + 1;
               [~,CSAP(i,l)] = sigFan( kData, SM, 4, evnd, Pflg2 );
               CSAP(i,l).AlgoName = ['G',num2str(i),'I',num2str(j)];
                CSAP(i,l)
           catch
               continue
           end
       end
    end
end
end
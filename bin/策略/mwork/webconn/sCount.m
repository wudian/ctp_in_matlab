function n = sCount( blV,ib,ie,dim )
%UNTITLED8 Summary of this function goes here
%   blV:  Bool vector/matrix
%   S = sum(X,DIM) sums along the dimension DIM. (2 by dedaul)

if nargin > 1
    if nargin == 2
        ie = ib;
        ib = 1;        
        dim = 2;
    end
    if nargin == 3
        dim = 2;
    end
    n = sum(blV(:,ib:ie),dim);
elseif nargin == 1
    n = sum(sum(blV));
end
end


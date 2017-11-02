load corpList.mat;
N=length(corpList);
corpList_S=cell(size(corpList));
for i=1:N
    cc = cell2mat(corpList_T(i));
    if(cc(1)=='0'||cc(1)=='3')
        corpList_S(i)=mat2cell(strcat(cc,'.SZ'));
    elseif(cc(1)=='6')
        corpList_S(i)=mat2cell(strcat(cc,'.SS'));
    end
end
        

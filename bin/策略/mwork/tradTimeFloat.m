function  tn = tradTimeFloat( SI,maxTick, itick )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
     
if itick<maxTick/2+1
    tn = (9+(SI*(itick-2)/3600))/24;
else
    tn = (13+(SI*(itick-ceil(maxTick/62))/3600))/24;
end
end
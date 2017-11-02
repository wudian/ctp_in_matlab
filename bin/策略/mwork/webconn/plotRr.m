function plotRr(RR,IM)

nf1 = numel(IM(:,1));

cc=jet(nf1);
figure; hold on; grid on;
lname = [];
for i = 1:nf1
    ph1(i) = plot(RR{IM(i,1)}(:,1),RR{IM(i,1)}(:,2),'*--','color',cc(mod(i,nf1)+1,:));
    lname{i} = ['L',num2str(IM(i,1))];
end
lgd=legend(ph1,lname,-1);
set(lgd,'EdgeColor','white');
title('Average Rate of Return Over Time')

figure; hold on; grid on;
for i = 1:nf1
    l = numel(RR{IM(i,1)})/2; % No of Selcted Algo
%     arr = [];
%     for j=1:l
%         %arr(j) = prod(RR{IM(i,1)}(1:j,2));
%         %arr(j) = log(prod(RR{IM(i,1)}(1:j,2)));  % Log Y-coordinate
% 
%     end
%    ph2(i) = plot(RR{IM(i,1)}(:,1),arr','*--','color',cc(mod(i,nf1)+1,:));
    ph2(i) = plot(RR{IM(i,1)}(:,1),RR{IM(i,1)}(:,3),'*--','color',cc(mod(i,nf1)+1,:));
end
lgd=legend(ph2,lname,-1);
set(lgd,'EdgeColor','white');
title('Accumulated Rate of Return Over Time')
end
function [ output, tradeDetail, output1, totalDiff] = Signal4( Open, High, Low ,Close, Date, Sig, maxLots, flag,ppoint,lpoint)
%% 本函数主要针对sig分别为BK，SP，SK， BP的信号，产生交易策略并在图中标出BS点
%maxLots:最大持仓量，默认为1，即最大只能有1笔持仓
%flag:是否要画图，1：画图，0：不画




if nargin==6
    maxLots=1;
    flag=0;
elseif nargin==7
    flag=0;
end
% if rem(maxLots,1)~=0
%     error('maxLots必须为正整数');
% end
% 
% if isempty(flag)
%     flag=0;
% end

Sig1=Sig(:,1);
Sig2=Sig(:,2);
Sig3=Sig(:,3);
Sig4=Sig(:,4);

%%如果Sig1，Sig2在同一时间点发出买入卖出信号，则不考虑
ind1=(Sig1==Sig2);
ind3=(Sig3==Sig4);
Sig1(ind1)=0;
Sig2(ind1)=0;
Sig3(ind3)=0;
Sig4(ind3)=0;

if sum(Sig1+Sig3)==0
%     error(message('MATLAB:signal2:nosignal'));
    disp('MATLAB:Signal2:没有产生交易信号');
end



%% 输出变量
%%交易频率，平均收益率，胜率
%%变量定义
%%单值变量
tradeNumber=0;%总交易次数
buyNumber=0;%多头交易次数
sellNumber=0;%空头交易次数
Position1=0;%多头仓位
Position2=0;%空头仓位
winNumber=0;%记录成功交易次数
ret=[];%%每次交易的收益率（考虑成本）
lret=[];%%每次交易的收益
cost=[];%%每次交易成本，第一列为手续费，第二列为递延费，第三列为点差
%%序列变量
inPrice1=[];%%多头建仓价格
outPrice1=[];%%多头平仓价格
inDate1={};%%进场时间
outDate1={};%%出场时间
inPos1=[];%%记录进场位置，利于作图
outPos1=[];%%记录出场位置，利于作图
inDire1=[];%%每次的进场的方向  1表示做多  -1表示做空
outDire1=[];%%每次的出场方向

inPrice2=[];%%空头建仓价格
outPrice2=[];%%空头平仓价格
inDate2={};%%进场时间
outDate2={};%%出场时间
inPos2=[];%%记录进场位置，利于作图
outPos2=[];%%记录出场位置，利于作图
%%交易记录输入输出需要用到的变量
inDire2=[];%%每次的进场的方向  1表示做多  -1表示做空
outDire2=[];%%每次的出场方向


if maxLots==1
    for i=1:length(Close)
        if Sig1(i)==1 && Position1==0
            Position1=1;
            buyNumber=buyNumber+1;
            inPrice1(buyNumber)=Close(i);
            inDire1(buyNumber)=1;
            inDate1(buyNumber)=Date(i);
            inPos1(buyNumber)=i;
        end
        %%止盈止损
        if Position1==1
            if exist('ppoint','var')  %%止盈
            if i>inPos1(buyNumber) && High(i)>(ppoint+inPrice1(buyNumber));
                Position1=0;
                outPrice1(buyNumber)=inPrice1(buyNumber)+ppoint;
                outDire1(buyNumber)=-1;
                outDate1(buyNumber)=Date(i);
                outPos1(buyNumber)=i;
            end
            end
            if exist('lpoint','var')  %%止损
            if i>inPos1(buyNumber) && Low(i)<(inPrice1(buyNumber)-lpoint);
                Position1=0;
                outPrice1(buyNumber)=inPrice1(buyNumber)-lpoint;
                outDire1(buyNumber)=-1;
                outDate1(buyNumber)=Date(i);
                outPos1(buyNumber)=i;
            end
            end
        end
        
        if Sig2(i)==1 && Position1==1
            Position1=0;
            outPrice1(buyNumber)=Close(i);
            outDire1(buyNumber)=-1;
            outDate1(buyNumber)=Date(i);
            outPos1(buyNumber)=i;
        end
        if Sig3(i)==1 && Position2==0
            Position2=-1;
            sellNumber=sellNumber+1;
            inPrice2(sellNumber)=Close(i);
            inDire2(sellNumber)=-1;
            inDate2(sellNumber)=Date(i);
            inPos2(sellNumber)=i;
        end
        %%止盈止损
        if Position2==-1
            if exist('ppoint','var')  %%止盈
            if i>inPos2(sellNumber) && Low(i)<(inPrice2(sellNumber)-ppoint);
                Position2=0;
                outPrice2(sellNumber)=inPrice2(sellNumber)-ppoint;
                outDire2(sellNumber)=1;
                outDate2(sellNumber)=Date(i);
                outPos2(sellNumber)=i;
            end
            end
            if exist('lpoint','var')  %%止盈
            if i>inPos2(sellNumber)  && High(i)>(inPrice2(sellNumber)+lpoint);
                Position2=0;
                outPrice2(sellNumber)=inPrice2(sellNumber)+lpoint;
                outDire2(sellNumber)=1;
                outDate2(sellNumber)=Date(i);
                outPos2(sellNumber)=i;
            end
            end
        end
        
        if Sig4(i)==1 && Position2==-1
            Position2=0;
            outPrice2(sellNumber)=Close(i);
            outDire2(sellNumber)=1;
            outDate2(sellNumber)=Date(i);
            outPos2(sellNumber)=i;
        end
        
        %最后交易周期如果未平仓，则不考虑最后一次交易
        if i==length(Close) && Position1==1
            Position1=0;
            inPrice1(buyNumber)=[];
            inDire1(buyNumber)=[];
            inDate1(buyNumber)=[];
            inPos1(buyNumber)=[];
            buyNumber=buyNumber-1;
        end
        if i==length(Close) && Position2==-1
            Position2=0;
            inPrice2(sellNumber)=[];
            inDire2(sellNumber)=[];
            inDate2(sellNumber)=[];
            inPos2(sellNumber)=[];
            sellNumber=sellNumber-1;
        end
        
    end
    
else %如果允许加仓
    for i=1:length(Close)
        if Sig1(i)==1 && (Position1-Position2)<maxLots
            Position1=Position1+1;
            buyNumber=buyNumber+1;
            inPrice1(buyNumber)=Close(i);
            inDire1(buyNumber)=1;
            inDate1(buyNumber)=Date(i);
            inPos1(buyNumber)=i;
        elseif Sig2(i)==1 && Position1>0
            
            outPrice1(buyNumber-Position1+1:buyNumber)=Close(i);
            outDire1(buyNumber-Position1+1:buyNumber)=-1;
            outDate1(buyNumber-Position1+1:buyNumber)=Date(i);
            outPos1(buyNumber-Position1+1:buyNumber)=i;
            Position1=0;
        end
        if Sig3(i)==1 && (Position1-Position2)<maxLots
            Position2=Position2-1; %做空单数
            sellNumber=sellNumber+1;
            inPrice2(sellNumber)=Close(i);
            inDire2(sellNumber)=-1;
            inDate2(sellNumber)=Date(i);
            inPos2(sellNumber)=i;
        elseif Sig4(i)==1 && Position2<0
            
            outPrice2(sellNumber+Position2+1:sellNumber)=Close(i);
            outDire2(sellNumber+Position2+1:sellNumber)=1;
            outDate2(sellNumber+Position2+1:sellNumber)=Date(i);
            outPos2(sellNumber+Position2+1:sellNumber)=i;
            Position2=0;
        end
        
        %最后交易周期如果未平仓，则不考虑最后一次交易
        if i==length(Close) && Position1>0
            
            inPrice1(end-Position1+1:end)=[];
            inDire1(end-Position1+1:end)=[];
            inDate1(end-Position1+1:end)=[];
            inPos1(end-Position1+1:end)=[];
            buyNumber=buyNumber-Position1;
            Position1=0;
        end
        if i==length(Close) && Position2<0
            
            inPrice2(end+Position2+1:end)=[];
            inDire2(end+Position2+1:end)=[];
            inDate2(end+Position2+1:end)=[];
            inPos2(end+Position2+1:end)=[];
            sellNumber=sellNumber+Position2;
            Position2=0;
        end
    end
    
end

inPrice=[inPrice1,inPrice2];
outPrice=[outPrice1,outPrice2];
inDate=[inDate1,inDate2];
outDate=[outDate1,outDate2];
inPos=[inPos1,inPos2];
outPos=[outPos1,outPos2];
inDire=[inDire1,inDire2];
outDire=[outDire1,outDire2];


[inPos, ind] = sort(inPos); %按入场点排序

outPos=outPos(ind);

inPrice=inPrice(ind);
outPrice=outPrice(ind);
inDate=inDate(ind);
outDate=outDate(ind);
inDire=inDire(ind);
outDire=outDire(ind);

tradeNumber=buyNumber+sellNumber;

%%计算每笔收益率（RetFun函数）
for i=1:tradeNumber
    date1=inDate(i);
    date2=outDate(i);
    date1=datestr(date1,'yyyy-mm-dd');
    date2=datestr(date2,'yyyy-mm-dd');
    %延期费天数Num,凌晨4点为分界线
    Num(i)=daysact(date1, date2);
    if hour(inDate(i))>4 && hour(outDate(i))<4 
        Num(i)=Num(i)-1;
    elseif hour(inDate(i))<4 && hour(outDate(i))>4
        Num(i)=Num(i)+1;
    end

    [ret(i),lret(i),cost(i,:)]=RetFun(inPrice(i),outPrice(i),inDire(i),Num(i));
% [ret(i),lret(i),cost(i,:)]=RetFunNoCost(inPrice(i),outPrice(i),inDire(i),Num(i));
%     [ret(i),lret(i),cost(i,:)]=RetFunnodc(inPrice(i),outPrice(i),inDire(i),Num(i));
% [ret(i),lret(i),cost(i,:)]=RetFun40(inPrice(i),outPrice(i),inDire(i),Num(i));
    
end

%  tradeDetail={};
%  tradeDetail{1,1}='进场时间';tradeDetail{1,2}='出场时间';tradeDetail{1,3}='进场方向';tradeDetail{1,4}='进场价格';
%  tradeDetail{1,5}='出场价格';tradeDetail{1,6}='每笔收益率';tradeDetail{1,7}='持有时间(天)';
% for i=1:tradeNumber
% tradeDetail{i+1,1}=inDate{i};tradeDetail{i+1,2}=outDate{i};tradeDetail{i+1,3}=inDire(i);
% tradeDetail{i+1,4}=inPrice(i);tradeDetail{i+1,5}=outPrice(i);tradeDetail{i+1,6}=ret(i);tradeDetail{i+1,7}=Num(i);
% end
% 
% % disp('交易记录详细表：');
% % disp(tradeDetail);
% 
% %交易频率
% % day0=datestr(Date(1),'yyyy-mm-dd');
% % dayend=datestr(Date(end),'yyyy-mm-dd');
% % Totaldays=daysact(day0,dayend);
% Totaldays=round(length(Close)/22); %每天22个交易小时
% Fre=tradeNumber/Totaldays; %单位：次/天
% 
% %平均收益率
% aveReturn=mean(ret);
% 
% %胜率
% winRatio=length(ret(ret>0))/tradeNumber;
% 
% %做多胜率
% bwin=length(ret(ret(inDire==1)>0))/buyNumber;
% 
% %做空胜率
% swin=length(ret(ret(inDire==-1)>0))/sellNumber;
% 
% %%交易绩效写入交易绩效表
% output{1,1}='胜率';output{1,2}='交易次数';output{1,3}='交易频率(次/天)';output{1,4}='平均收益率';output{1,5}='最大单次盈利';output{1,6}='最大单次亏损';
% output{1,7}='做多次数';output{1,8}='做多胜率';output{1,9}='做空次数';output{1,10}='做空胜率';
% output{2,1}=winRatio;output{2,2}=tradeNumber;output{2,3}=Fre;output{2,4}=aveReturn;output{2,5}=max(ret);output{2,6}=min(ret);
% output{2,7}=buyNumber;output{2,8}=bwin;output{2,9}=sellNumber;output{2,10}=swin;
% % disp('交易绩效列表如下：');
% % disp(output);




if tradeNumber<=0
    disp('MATLAB:Signal1:没有产生交易信号');
end

iniCap=100000; %初始资金10w
finCap=iniCap+sum(lret);
totalRet=(finCap-iniCap)/iniCap;
ljret=cumsum(lret); %累计盈利
tradeCost=sum(cost,2);%每次交易成本

holdCycle=[]; %持有周期
tradeDiff=zeros(size(Close));
% if maxLots==1
%     if tradeNumber>0
%         holdCycle=outPos-inPos; %持有周期（小时）
%         tradeDiff(outPos)=lret';
%     end
%     totalDiff=iniCap+cumsum(tradeDiff);
% else
if ~isempty(inPos) & ~isempty(outPos)
[~,ind]=sortrows([outPos,inPos],[1,2]);
outPos0=outPos;
outPos0(:,1)=outPos(ind);%%按出场点排序，计算累计收益率
lret1=lret;
lret1(:,1)=lret(ind);
end
    if tradeNumber>0
        tradeDiff(outPos0(1))=lret(1);
        holdCycle=outPos-inPos; %持有周期（小时）
        %% 如果是4小时的数据，holdCycle要乘以4
        for i=2:tradeNumber
            if outPos0(i)==outPos0(i-1)
                tradeDiff(outPos0(i))=lret1(i)+tradeDiff(outPos0(i));
            else
                tradeDiff(outPos0(i))=lret1(i);
            end
        end
        totalDiff=iniCap+cumsum(tradeDiff);
    else
        totalDiff=zeros(size(Close));
    end
% end

 tradeDetail={};
 tradeDetail{1,1}='进场时间';tradeDetail{1,2}='出场时间';tradeDetail{1,3}='进场方向';tradeDetail{1,4}='进场价格';
 tradeDetail{1,5}='出场价格';tradeDetail{1,6}='每笔收益率';tradeDetail{1,7}='每笔盈利';tradeDetail{1,8}='持有时间(天)';tradeDetail{1,9}='交易成本';tradeDetail{1,10}='累计盈利';
for i=1:tradeNumber
tradeDetail{i+1,1}=inDate{i};tradeDetail{i+1,2}=outDate{i};tradeDetail{i+1,3}=inDire(i);
tradeDetail{i+1,4}=inPrice(i);tradeDetail{i+1,5}=outPrice(i);tradeDetail{i+1,6}=ret(i);
tradeDetail{i+1,7}=lret(i);tradeDetail{i+1,8}=Num(i);tradeDetail{i+1,9}=tradeCost(i);
tradeDetail{i+1,10}=ljret(i);
end

% disp('交易记录详细表：');
% disp(tradeDetail);

%交易频率
day0=datestr(Date(1),'yyyy-mm-dd');
dayend=datestr(Date(end),'yyyy-mm-dd');
% Totaldays=daysact(day0,dayend);
% Totaldays=round(length(Close)/22); %每天22个交易小时
Totaldays=416;
Fre=tradeNumber/Totaldays; %单位：次/天

%平均收益率
aveReturn=mean(ret);

%胜率
winRatio=length(ret(ret>0))/tradeNumber;

%做多胜率
bwin=length(ret(ret(inDire==1)>0))/buyNumber;

%做空胜率
swin=length(ret(ret(inDire==-1)>0))/sellNumber;
if isnan(bwin)
    bwin=0;
end
if isnan(swin)
    swin=0;
end

%%交易绩效写入交易绩效表
output={};
output{1,1}='胜率';output{1,2}='交易次数';output{1,3}='交易频率(次/天)';output{1,4}='平均收益率';output{1,5}='最大单次盈利';output{1,6}='最大单次亏损';
output{1,7}='做多次数';output{1,8}='做多胜率';output{1,9}='做空次数';output{1,10}='做空胜率';output{1,11}='总收益率';output{1,12}='总成本';
output{2,1}=winRatio;output{2,2}=tradeNumber;output{2,3}=Fre;output{2,4}=aveReturn;output{2,5}=max(ret);output{2,6}=min(ret);
output{2,7}=buyNumber;output{2,8}=bwin;output{2,9}=sellNumber;output{2,10}=swin;output{2,11}=totalRet;output{2,12}=sum(tradeCost);
% disp('交易绩效列表如下：');
% disp(output);






%%输出output的详细信息
%%初始资金10W，每次开仓1标准手
%%总收益率=(finCap-iniCap)/iniCap;
%%平均收益率=mean(ret) %与初始资金无关
%%平均每次盈利=mean(lret)
if min(totalDiff)>0
    maxd=maxdrawdown(totalDiff);
else
    maxd=1;
end
output1={};
output1{1,1}='模型的详细交易信息';
output1{2,1}='测试天数';output1{2,2}=Totaldays;output1{2,4}='测试周期数';output1{2,5}=length(Close);
output1{3,1}='指令总数'; output1{3,2}=tradeNumber;output1{3,4}='平均交易周期';output1{3,5}=floor(length(Close)/tradeNumber);
output1{4,1}='初始资金'; output1{4,2}=iniCap; output1{4,4}='最终权益'; output1{4,5}=finCap;
output1{5,1}='总收益率'; output1{5,2}=totalRet; output1{5,4}='总盈利'; output1{5,5}=finCap-iniCap;
output1{6,1}='扣除最大盈利后收益率'; output1{6,2}=(finCap-iniCap-lret(ret==max(ret)))/iniCap; output1{6,4}='扣除最大亏损后收益率'; output1{6,5}=(finCap-iniCap-lret(ret==min(ret)))/iniCap; 

output1{8,1}='可靠性(胜率)'; output1{8,2}=winRatio;
output1{9,1}='总交易次数'; output1{9,2}=tradeNumber;output1{9,4}='资金最大回撤'; output1{9,5}=maxd;
output1{10,1}='盈利次数比例';output1{10,2}=winRatio;output1{10,4}='亏损次数比例';output1{10,5}=1-winRatio;
output1{11,1}='平均收益率';output1{11,2}=aveReturn;output1{11,4}='平均每次盈利';output1{11,5}=mean(lret);
output1{12,1}='标准离差率';output1{12,2}=std(ret)/aveReturn;output1{12,4}='标准离差';output1{12,5}=std(ret);
output1{13,1}='多头次数';output1{13,2}=buyNumber;output1{13,4}='空头次数';output1{13,5}=sellNumber;
output1{14,1}='多头盈利次数';output1{14,2}=bwin*buyNumber;output1{14,4}='空头盈利次数';output1{14,5}=swin*sellNumber;

output1{16,1}='盈利次数';output1{16,2}=round(winRatio*tradeNumber);output1{16,4}='亏损次数';output1{16,5}=tradeNumber-round(winRatio*tradeNumber);
output1{17,1}='总盈利额';output1{17,2}=sum(lret(ret>0));output1{17,4}='总亏损额';output1{17,5}=-sum(lret(ret<0));
output1{18,1}='最大盈利额';output1{18,2}=max(lret);output1{18,4}='最大亏损额';output1{18,5}=-min(lret);
output1{19,1}='最大收益率';output1{19,2}=max(ret);output1{19,4}='最小收益率';output1{19,5}=min(ret);
output1{20,1}='平均盈利周期';output1{20,2}=mean(holdCycle(ret>0));output1{20,4}='平均亏损周期';output1{20,5}=mean(holdCycle(ret<0));

if isnan(output1{20,5})
    output1{20,5}=0;
end
if isnan(output1{20,2})
    output1{20,3}=0;
end
% output1{21,1}='最大连续盈利周期';output1{21,2}=max(holdCycle(ret>0));output1{21,4}='最大连续亏损周期';output1{21,5}=max(holdCycle(ret<0));
% output1{22,1}='最大连续盈利';output1{22,2}=max(holdCycle(ret>0));output1{21,4}='最大连续亏损周期';output1{21,5}=max(holdCycle(ret<0));
%计算空仓时间
cyc1=outPos(1:end-1)-inPos(2:end);
kctime=length(Close)-(sum(holdCycle)-sum(cyc1(cyc1>0)));
output1{21,1}='空仓总时间(小时)';output1{21,2}=kctime;output1{21,4}='空仓时间/总时间';output1{21,5}=kctime/length(Close);

output1{22,1}='平均持仓周期';output1{22,2}=mean(holdCycle);
%成本部分
if tradeNumber>=1
percost=sum(cost,1);%成本分类，手续费，递延费，点差总和
output1{23,1}='总成本';output1{23,2}=sum(tradeCost);output1{23,4}='手续费总和';output1{23,5}=percost(1);
output1{24,1}='递延费总和';output1{24,2}=percost(2);output1{24,4}='点差总计';output1{24,5}=percost(3);
end











%% 作图
% 
% clf;
% %% 图1
% subplot('Position',[0.13 0.38 0.775 0.54])%%双图，大图显示K线和资金曲线，小图显示指标线（比如KD）
% 
% [AX,H1,H2] =plotyy(1:length(Close),Close,1:length(totalDiff),totalDiff);
% % set(gca,'Xtick',[0 500,1000,1500,2000],...'XtickLabel','22-Jan-2006|22-Jan-2006|22-Jan-2007|22-Jan-2008|22-Jan-2009');
% tick1=get(gca,'XTick');
% % xlabel=datestr([Date{1},Date{tick1(2:end-1)}])
% % datenum(year(Date{tick1(2:end-1)}),month(Date{tick1(2:end-1)}),day(Date{tick1(2:end-1)}))
% xlb=Date{1};
% for i=2:length(tick1)-1
%     xlb=[xlb,'|',Date{tick1(i)}];
% end
% 
% 
% 
% %%标记买卖点
% %粉色表示建仓，绿色表示平仓
% text(inPos(inDire==1),Close(inPos(inDire==1))-1,'\uparrow','Color','m','FontWeight','bold');
% text(inPos(inDire==-1),Close(inPos(inDire==-1))+1,'\downarrow','Color','m','FontWeight','bold');
% text(outPos(outDire==1),Close(outPos(outDire==1))-1,'\uparrow','Color','g','FontWeight','bold');
% text(outPos(outDire==-1),Close(outPos(outDire==-1))+1,'\downarrow','Color','g','FontWeight','bold');
% 
% set(AX(2),'XColor','k','YColor','r');
% set(AX(1),'Xtick',tick1(1:end-1));
% set(AX(2),'Xtick',tick1(1:end-1));
% set(AX(1),'XtickLabel',xlb);
% set(AX(2),'XtickLabel',[]);
% 
% HH1=get(AX(1),'Ylabel');
% set(HH1,'String','收盘价');
% set(HH1,'color','b');
% set(HH1,'FontSize',20);
% HH2=get(AX(2),'Ylabel');
% set(HH2,'String','资金曲线');
% set(HH2,'color','r');
% set(HH2,'FontSize',20);
% 
% set(H2,'color','r');
% 
% % set(H2,'Color','r');
% grid on;
% 
% set(gca,'XColor','b');
% ch=get(gca,'XTickLabel');
% ch1=ch(:,1:10);
% ch1(1,:)='          ';
% set(gca,'XTickLabel',ch1);
% title('价格走势与资金曲线图','FontSize',20);
% 
% if flag==1
% 
% %% 作图，标出BS点
% plotbar=[Open,High,Low,Close];
% cndlV2(plotbar,Date,'r','b');
% hold on;
% % set(gca,'XTickLabel',['0',Date(1000:1000:end)]);
% grid on;
% % whitebg('k');
% set(gca,'YLim',[2000 9000]);
% %%标记买卖点
% for i=1:tradeNumber
%     if inDire(i)==1
%         text(inPos(i),Low(inPos(i))-1,{'\uparrow';'BK'},'FontSize',8,'FontUnits','normalized');
%     else
%         text(inPos(i),High(inPos(i))+3,{'SK';'\downarrow'},'FontSize',8,'FontUnits','normalized');
%     end
%     if outDire(i)==1
%         text(inPos(i),Low(inPos(i))-1,{'\uparrow';'BP'},'FontSize',8,'FontUnits','normalized');
%     else
%         text(inPos(i),High(inPos(i))+3,{'SP';'\downarrow'},'FontSize',8,'FontUnits','normalized');
%     end
% end
% end
% end


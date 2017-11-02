function signal = find_mv(daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [ATR快线周期p ATR慢线周期q 前m根K线 开口下限 最后n分钟不操作]; %% 
%% inpara{2} = sec_points; %% [1 75 135 175 215];
%%
%%% OUTPUT
%% signal.name = 
%% signal.inplace =  []     VECTOR
%% signal.direct  =  []     BOOL +1 or -1
%% signal.inprice =  []     VECTOR   daydata(signal.inplace,1);  

%%% Step 0: INPUT check 
%%% 


%%% Step 1: Find price break point, and output its next point. 

p=inpara{1}(1);%a=34 快线周期
q=inpara{1}(2); %b=-20 慢线周期
lim_down=inpara{1}(4);%3 前m根K线
n=inpara{1}(5);%0 开口下限
m=inpara{1}(3);%5 最后n分钟不操作

len_day = inpara{2}(end);  %% sec_points(end); 
mv_1=zeros(len_day,1);
mv_2=zeros(len_day,1);
mv=zeros(len_day,1);
for i=p:len_day
    mv_1(i)=sum(daydata(i-p+1:i,4))/p;  
end
for i=q:len_day
    mv_2(i)=sum(daydata(i-q+1:i,4))/q;  
    mv(i)=abs(mv_1(i)-mv_2(i));
end

k = 0; %% number of signal
k1 = 0;
k2 = 0; 

for i = 20:len_day - n-1
    
    if mv_1(i-1) < mv_2(i-1) && mv_1(i) > mv_2(i) && daydata(i,4)>mv_1(i) && daydata(i+1,4)>mv_1(i+1) && daydata(i,4)>=daydata(i,1)...
            && daydata(i+1,4)>=daydata(i+1,1) && max(mv(i-m:i-1))>=lim_down       
            k = k + 1; 
          if k1 ==0
            k1 = 1; 
          else
              k1 = k1 + 1;
          end
           signal.inplace(k1+k2) = i+2 ;      %% OUTPUT 2 
           signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
           signal.break(k1+k2)= i+2;
           signal.inprice(k1+k2) = daydata(i+2,1);                 
   elseif mv_1(i-1) > mv_2(i-1) && mv_1(i) < mv_2(i)  && daydata(i,4)<mv_1(i) && daydata(i+1,4)<mv_1(i+1) && daydata(i,4)<=daydata(i,1)...
           && daydata(i+1,4)<=daydata(i+1,1)  && max(mv(i-m:i-1))>=lim_down 
            k = k + 1; 
          if  k2 ==0
                k2 = 1; 
          else
              k2=k2+1;
          end
            signal.inplace(k1 + k2) = i+2;       %% OUTPUT 2 
            signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
            signal.break(k1+k2)= i+2;
          signal.inprice(k1 + k2) = daydata(i+2,1);   %% OUTPUT 4                        
    end
 end

    
if k > 0
   signal.name = 'mv';  %% OUTPUT 1
else
    signal = {};
end
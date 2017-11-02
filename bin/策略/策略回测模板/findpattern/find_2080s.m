function signal = find_2080s(hisdata,daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [间隔时间t 滑点c 收盘前n分钟不操作 影线百分比]; %% 
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
t = inpara{1}(1);  c = inpara{1}(2);  n = inpara{1}(3); 
len_day = inpara{2}(end);  %% sec_points(end); 
multi=inpara{1}(4);
hisamp=max(hisdata(:,2))-min(hisdata(:,3));
k = 0; %% number of signal
k1 = 0;
k2 = 0; 

if max(hisdata(:,2))-hisdata(1,1)<=hisamp*multi && hisdata(len_day,4)- min(hisdata(:,3))<=hisamp*multi && max(daydata(1:t,2))<min(hisdata(:,3))
for i = t+1:len_day - n 

        if daydata(i,2) >= min(hisdata(:,3)) + c
            k = k + 1; 
          if k1 ==0
            k1 = 1; 
          else
              k1 = k1 + 1;
          end
            signal.inplace(k1+k2) = i ;      %% OUTPUT 2 
            signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
            signal.break(k1+k2)= i;
           
            if daydata(i,3) <= min(hisdata(:,3))  + c
                signal.inprice(k1+k2) = min(hisdata(:,3)) + c; 
            elseif daydata(i,1) >= min(hisdata(:,3)) + c         %% OUTPUT 4
                signal.inprice(k1+k2) = daydata(i,1); 
            end
         
        end
end
elseif max(hisdata(:,2))-hisdata(len_day,4)<=hisamp*multi && hisdata(1,1) - min(hisdata(:,3))<=hisamp*multi && min(daydata(1:t,3))>max(hisdata(:,2))
    for i=t+1:len_day-n
        if daydata(i,3) <= max(hisdata(:,2)) - c
            k = k + 1; 
          if  k2 ==0
                k2 = 1; 
          else
              k2=k2+1;
          end
            signal.inplace(k1 + k2) = i;       %% OUTPUT 2 
            signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
            signal.break(k1+k2)= i;
            if daydata(i,2) >= max(hisdata(:,2)) - c
                signal.inprice(k1 + k2) = max(hisdata(:,2)) - c; 
            elseif daydata(i,1) <= max(hisdata(:,2)) - c
                signal.inprice(k1 + k2) = daydata(i,1);   %% OUTPUT 4
            end  
       end
  
 
    end
 end

if k > 0
   signal.name = '2080s';  %% OUTPUT 1
else
    signal = {};
end
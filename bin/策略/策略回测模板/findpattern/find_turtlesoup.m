function signal = find_turtlesoup(daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [移动时间p 间隔时间t 影线长度a 极值点成交量下限b 下挂点数c 收盘前n分钟不操作]; %% 
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
p = inpara{1}(1);  t = inpara{1}(2);  a = inpara{1}(3); 
b = inpara{1}(4); c = inpara{1}(5);  n = inpara{1}(6);
len_day = inpara{2}(end);  %% sec_points(end); 
k = 0; %% number of signal
k1 = 0;
k2 = 0; flag_1=1;flag_2=1;
% t_max = 1; t_min = 1;
% y_max = max(daydata(1:p,2)); y_min = min(daydata(1:p,3)); 
for i = p:len_day - n 
%    [y_max,t_max] = max(daydata(i-p+1:i,2)); [y_min,t_min] = min(daydata(i-p+1:i,3));
%    t_max = i-p+1+t_max; t_min = i-p+1+t_min;
     for j=i-p+1:i-1
        if daydata(j,2)>=daydata(i,2)
            flag_1=0;
            break;
        end
     end
     if j ==i-1 && flag_1==1
         flag_1=1;
     else 
         flag_1=0;
     end
     for j=i-p+1:i-1
        if daydata(j,3)<=daydata(i,3)
            flag_2=0;
            break;
        end
     end
     if j ==i-1 && flag_2==1
         flag_2=1;
     else 
         flag_2=0;
     end 
        
    if daydata(i,2)-daydata(i,4) > a && daydata(i,5)>=b*daydata(i-1,5) && flag_1==1 
        for s = i+t+1:len_day-n
         if min(daydata(i+1:i+t,3)) > daydata(i,4) - c && daydata(s,3) <= daydata(i,4) - c && daydata(s-1,3) > daydata(i,4) - c
%          if daydata(s-1,3) > daydata(i,4) - c && daydata(s,3) <= daydata(i,4) - c   
            k = k + 1; 
          if k1 ==0
            k1 = 1; 
          else
              k1 = k1 + 1;
          end
            signal.inplace(k1+k2) = s ;      %% OUTPUT 2 
            signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
            signal.break(k1+k2) = s;
           
            if daydata(s,2) >= daydata(i,4) - c 
                signal.inprice(k1+k2) = daydata(i,4) - c; 
            elseif daydata(s,1) <= daydata(i,4) - c         %% OUTPUT 4
                signal.inprice(k1+k2) = daydata(i,4) - c; 
            end
         signal.stop(k1+k2) = daydata(i,2);
        end
        end
    elseif daydata(i,4)-daydata(i,3) > a && daydata(i,5)>=b*daydata(i-1,5) && flag_2==1 
        for s = i+t+1:len_day-n
            
         if max(daydata(i+1:i+t,2)) < daydata(i,4) + c && daydata(s,2) >= daydata(i,4) + c && daydata(s-1,2) < daydata(i,4) + c
%           if daydata(s-1,2) < daydata(i,4) + c && daydata(s,2) >= daydata(i,4) + c
            k = k + 1; 
          if  k2 ==0
                k2 = 1; 
          else
              k2=k2+1;
          end
            signal.inplace(k1 + k2) = s;       %% OUTPUT 2 
            signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
            signal.break(k1+k2) = s;
            if daydata(s,3) <= daydata(i,4) + c 
                signal.inprice(k1 + k2) = daydata(i,4) + c ; 
            elseif daydata(s,1) >= daydata(i,4) + c 
                signal.inprice(k1 + k2) = daydata(s,1);   %% OUTPUT 4
            end 
          signal.stop(k1+k2) = daydata(i,3);   
        end
        end
end
  
     flag_1=1;flag_2=1; 
    end



if k > 0
   signal.name = 'turtlesoup';  %% OUTPUT 1
else
    signal = {};
end

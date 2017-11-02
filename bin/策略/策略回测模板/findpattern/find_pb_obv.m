function signal = find_pb_obv(daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [间隔时间t 滑点c 收盘前n分钟不操作 OBV阈值下限 OBV阈值上限]; %% 
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
lim_down =  inpara{1}(4);
lim_up = inpara{1}(5);
len_day = inpara{2}(end);  %% sec_points(end); 
k = 0; %% number of signal
k1 = 0;
k2 = 0; 
t_max = 1; t_min = 1;
y_max = daydata(1,2); y_min = daydata(1,3); 
for i = 1:len_day - n 
%     if i ==1
    obv =  sum( daydata(1:i,5) .*  (daydata(1:i,4) - daydata(1:i,1) > 0)   -    daydata(1:i,5) .*  (daydata(1:i,4) - daydata(1:i,1) < 0) ) ;      % 正方向 + 负方向 - 1 
%     else
%     obv =  sum( daydata(1:i-1,5) .*  (daydata(1:i-1,4) - daydata(1:i-1,1) > 0)   -    daydata(1:i-1,5) .*  (daydata(1:i-1,4) - daydata(1:i-1,1) < 0) ) ;      % 正方向 + 负方向 - 1     
%     end
    if daydata(i,2) > y_max 
        if daydata(i,2) >= y_max + c && i >= t_max + t && obv >= lim_up 
            k = k + 1; 
          if k1 ==0
            k1 = 1; 
          else
              k1 = k1 + 1;
          end
            signal.inplace(k1+k2) = i ;      %% OUTPUT 2 
            signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
           
            if daydata(i,3) <= y_max + c
                signal.inprice(k1+k2) = y_max + c; 
            elseif daydata(i,1) >= y_max + c         %% OUTPUT 4
                signal.inprice(k1+k2) = daydata(i,1); 
            end
         
        end
      y_max = daydata(i,2); t_max = i; 
    elseif daydata(i,3) < y_min 
        if daydata(i,3) <= y_min - c && i >= t_min + t && obv <=lim_down
            k = k + 1; 
          if  k2 ==0
                k2 = 1; 
          else
              k2=k2+1;
          end
            signal.inplace(k1 + k2) = i;       %% OUTPUT 2 
            signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
            if daydata(i,2) >= y_min - c
                signal.inprice(k1 + k2) = y_min - c; 
            elseif daydata(i,1) <= y_min - c
                signal.inprice(k1 + k2) = daydata(i,1);   %% OUTPUT 4
            end  
          end
  
     y_min = daydata(i,3); t_min = i;  
    end
 end

if k > 0
   signal.name = 'price_break_obv';  %% OUTPUT 1
else
    signal = {};
end
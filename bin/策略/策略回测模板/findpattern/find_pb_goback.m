function signal = find_pb_goback(daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [间隔时间t 滑点c 收盘前n分钟不操作 一次止盈点 止损 回撤下限]; %% 
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
t = inpara{1}(1);  c = inpara{1}(2);  n = inpara{1}(3); target = inpara{1}(4); 
loss = inpara{1}(5); goback = inpara{1}(6); 
len_day = inpara{2}(end);  %% sec_points(end); 
k = 0; %% number of signal
k1 = 0; 
k2 = 0; k3 = 0;k4 = 0;
t_max = 1; t_min = 1;
y_max = daydata(1,2); y_min = daydata(1,3); 
for i = 1:len_day - n 
    if daydata(i,2) > y_max  
        if daydata(i,2) >= y_max + c && i >= t_max + t 
            k = k + 1; 
          if k1 ==0
            k1 = 1; 
          else
              k1 = k1 + 1;
          end
           if daydata(i,3) <= y_max + c
                break_price = y_max + c; 
           elseif daydata(i,1) >= y_max + c         %% OUTPUT 4
                break_price = daydata(i,1); 
           end
          if k1~=0
%               [x1 x2] = max(daydata(1:i,2));
%                maxprof = x1 - break_price;
%                minprof = 0;
              for k = i:len_day - n-1
                 [x1 x2] = max(daydata(i:k,2));
                 maxprof = x1 - break_price;
                 minprof = break_price - min(daydata(i:k,3));
                 for j=k:len_day - n-1
                 if maxprof >=target && minprof < loss && daydata(j-1,3) - daydata(j,3)==5 && daydata(j-1,3) - daydata(j-2,3)==5 && daydata(j,2) <= max(daydata(1:j,2))-goback
                   k3 = k3+1; 
%                   signal = {};
%                  if daydata(j,3) <= x1 + c
%                 signal.inprice(k3+k4) = x1 + c; 
%                  elseif daydata(j,1) >= x1 + c         %% OUTPUT 4
                signal.inprice(k3+k4) = daydata(j+1,1); 
%                  end
            signal.inplace(k3+k4) = j ;      %% OUTPUT 2 
            signal.direct(k3+k4) = +1;       %% OUTPUT 3 +1
            
%                  else 
%                      k1 = 0;
%                      clear signal.inprice
                
             [x1 x2] = max(daydata(1:j,2));
             maxprof = x1 - signal.inprice(k3+k4);
             minprof = signal.inprice(k3+k4) - min(daydata(i+1:j,3)); 
              break;
                 end
                 end
              end
          end
%             signal.inplace(k1+k2) = i ;      %% OUTPUT 2 
%             signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
           
%             if daydata(i,3) <= y_max + c
%                 signal.inprice(k1+k2) = y_max + c; 
%             elseif daydata(i,1) >= y_max + c         %% OUTPUT 4
%                 signal.inprice(k1+k2) = daydata(i,1); 
%             end
         
        end
      y_max = daydata(i,2); t_max = i; 
    elseif daydata(i,3) < y_min 
        if daydata(i,3) <= y_min - c && i >= t_min + t
            k = k + 1; 
          if  k2 ==0
                k2 = 1; 
          else
              k2=k2+1;
          end
             if daydata(i,2) >= y_min - c
                break_price = y_min - c; 
            elseif daydata(i,1) <= y_min - c
                break_price = daydata(i,1);   %% OUTPUT 4
            end  
          if k2~=0
%               [y1 y2] = min(daydata(1:i,3));
%                maxprof = break_price-min(daydata(1:i,3));
%                minprof = 0;
              for k = i:len_day - n-1
                 [y1 y2] = min(daydata(i:k,3));
                 maxprof = break_price-min(daydata(i:k,3));
                 minprof = max(daydata(i:k,2))- break_price;
                 for j=k:len_day - n-1
                 if maxprof >=target && minprof < loss  && daydata(j-1,2) - daydata(j,2)==5 && daydata(j-1,2) - daydata(j-2,2)==5 && daydata(j,3) >= min(daydata(1:j,3))+goback
                    k4 = k4+1;
%                     signal = {};
%                  if daydata(j,2) >= y1 - c
%                 signal.inprice(k3+k4) = y1 - c; 
%                  elseif daydata(j,1) <= y1 - c         %% OUTPUT 4
                signal.inprice(k3+k4) = daydata(j+1,1); 
%                  end
            signal.inplace(k3+k4) = j ;      %% OUTPUT 2 
            signal.direct(k3+k4) = -1;       %% OUTPUT 3 +1
            
%                  else 
%                      k2 = 0;
%                      clear signal.inprice
               
            [y1 y2] = min(daydata(1:j,3));
            maxprof = signal.inprice(k3+k4)-min(daydata(1:j,3));
            minprof = max(daydata(i+1:j,2))- signal.inprice(k3+k4);
            break;
                 end
                 end
              end
          end
%             signal.inplace(k1 + k2) = i;       %% OUTPUT 2 
%             signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
%             if daydata(i,2) >= y_min - c
%                 signal.inprice(k1 + k2) = y_min - c; 
%             elseif daydata(i,1) <= y_min - c
%                 signal.inprice(k1 + k2) = daydata(i,1);   %% OUTPUT 4
%             end  
           
     end
  
     y_min = daydata(i,3); t_min = i;  
    end
    if k3 ~= 0 || k4 ~= 0
        break;
    end
 end

if k3 ~= 0 || k4 ~= 0
   signal.name = 'price_break_goback';  %% OUTPUT 1
else
    signal = {};
end
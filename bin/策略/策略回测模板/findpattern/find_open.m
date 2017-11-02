function signal = find_open(hisdata,daydata, inpara) 
%%% 价格突破
%%% INPUT
%% daydata : data in a day [开盘价 最高价 最低价 收盘价]
%% inpara{1} = [进场时间t 滑点c 昨日波幅实体下线 跳空幅度上限]; %% 
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
t = inpara{1}(1);  c = inpara{1}(2); amp = inpara{1}(3); break_amp=inpara{1}(4);
len_day = inpara{2}(end);  %% sec_points(end); 
k = 0; %% number of signal
flag=0;
if hisdata(1,1)-hisdata(len_day,4)>=amp && abs(hisdata(len_day,4)-daydata(1,1))<=break_amp
    flag=-1;
elseif hisdata(len_day,4)-hisdata(1,1)>=amp && abs(hisdata(len_day,4)-daydata(1,1))<=break_amp
    flag=1;
end
if flag==1
    k=k+1;
    signal.inplace(k) = t ;      %% OUTPUT 2 
    signal.direct(k) = +1;       %% OUTPUT 3 +1
    signal.break(k)= t;
    signal.inprice(k) =daydata(t,1)+c;
elseif flag==-1
     k=k+1;
    signal.inplace(k) = t ;      %% OUTPUT 2 
    signal.direct(k) = -1;       %% OUTPUT 3 +1
    signal.break(k)= t;
    signal.inprice(k) =daydata(t,1)-c;
end
% t_max = 1; t_min = 1;
% y_max = daydata(1,2); y_min = daydata(1,3); 
% for i = 1:len_day - n 
%     if daydata(i,2) > y_max+c  
%         if (daydata(i,2) >= y_max + c && i >= t_max + t) && (daydata(i-1,3) < y_max + c || daydata(i-1,3) > y_max + c)
%             k = k + 1; 
% %             if k>m
% %                 break;
% %             end
%           if k1 ==0
%             k1 = 1; 
%           else
%               k1 = k1 + 1;
%           end
%             signal.inplace(k1+k2) = i ;      %% OUTPUT 2 
%             signal.direct(k1+k2) = +1;       %% OUTPUT 3 +1
%             signal.break(k1+k2)= t_max;
%            
%             if daydata(i,3) <= y_max + c
%                 signal.inprice(k1+k2) = y_max + c; 
%             elseif daydata(i,1) >= y_max + c         %% OUTPUT 4
%                 signal.inprice(k1+k2) = daydata(i,1); 
%             end
%          
%         end
%         if daydata(i,2) > y_max
%            y_max = daydata(i,2); t_max = i;
%         end
%     elseif daydata(i,3) < y_min -c
%         if (daydata(i,3) <= y_min - c && i >= t_min + t) && (daydata(i-1,2) > y_min - c || daydata(i-1,2) < y_min - c)
%             k = k + 1; 
% %             if k>m
% %                 break;
% %             end
%           if  k2 ==0
%                 k2 = 1; 
%           else
%               k2=k2+1;
%           end
%             signal.inplace(k1 + k2) = i;       %% OUTPUT 2 
%             signal.direct(k1 + k2) = -1;       %% OUTPUT 3 -1
%             signal.break(k1+k2)= t_min;
%             if daydata(i,2) >= y_min - c
%                 signal.inprice(k1 + k2) = y_min - c; 
%             elseif daydata(i,1) <= y_min - c
%                 signal.inprice(k1 + k2) = daydata(i,1);   %% OUTPUT 4
%             end  
%           end
%   if daydata(i,3) < y_min
%      y_min = daydata(i,3); t_min = i;  
%   end
%     end
%  end

if k > 0
   signal.name = 'open';  %% OUTPUT 1
else
    signal = {};
end
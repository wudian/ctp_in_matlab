function signal = find_sr(hisdata, daydata, inpara) 
%%% 固定时间突破 (一天一次进场？)
%%% INPUT
%% hisdata : data in yesterday [开盘价 最高价 最低价 收盘价]
%% daydata : data in today  [开盘价 最高价 最低价 收盘价]
%% inpara{1} =  [昨日波幅上限 昨日波幅下限 单位波动点数 收盘前n分钟不操作]; %% 
%% inpara{2} = sec_points; %% [1 75 135 175 215];
%%
%%% OUTPUT
%% signal.name =            STRING 
%% signal.inplace =  []     VECTOR
%% signal.direct  =  []     BOOL +1 or -1
%% signal.inprcie =  []     VECTOR

%%% Step 0: INPUT check 
%%%  t + n < len_day ( shuold hold )

lim_up =  inpara{1}(1);lim_down =  inpara{1}(2);
c =  inpara{1}(3); n =  inpara{1}(4); 

len_day = inpara{2}(end); 
amp=max(hisdata(:,2))-min(hisdata(:,3));
%%% Step 1: Compute amplitude and max, min in daydata(1:t,:);
pivot = (max(hisdata(:,2)) + min(hisdata(:,3))+hisdata(len_day,4))/3; 
r1=2*pivot-min(hisdata(:,3));
s1=2*pivot-max(hisdata(:,2));
r2=pivot+(r1-s1);s2=pivot-(r1-s1);
r3=max(hisdata(:,2))-2*(min(hisdata(:,3))-pivot);
s3=min(hisdata(:,3))-2*(max(hisdata(:,2))-pivot);


%%% Step 2:  Find fix time break point. 
% if t + n > len_day 
%     disp('wrong parameters for find_ft : t + n < len_day should hole')
% end
k = 0; 
if amp<=lim_up && amp>=lim_down
for i = 2 : len_day -n
%     if y_max - y_min >= p1 * amp  && daydata(i,2) >= y_max + c && daydata(i-1,2) < y_max + c && ... 
%        y_max - y_min >= p2 * amp  && daydata(i,3) <= y_min - c && daydata(i-1,3) >  y_min - c   %% 同时满足，不操作
  
    if daydata(i-1,2) <r1 && daydata(i,2)>=r1      %% 波幅大于做多比
%         if (daydata(i,2) >= y_max + c && daydata(i-1,2) < y_max + c) || (daydata(i,2) >= y_max + c && daydata(i-1,2) > y_max + c)

           k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = 1;         %% OUTPUT 3 +1
           if daydata(i,3)<=r1
           signal.inprice(k) = ceil(r1/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;

    elseif daydata(i-1,2) <r2 && daydata(i,2)>=r2
           k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = -1;         %% OUTPUT 3 +1
           if daydata(i,3)<=r2
           signal.inprice(k) = ceil(r2/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;
    elseif daydata(i-1,2) <r3 && daydata(i,2)>=r3
        
     k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = -1;         %% OUTPUT 3 +1
           if daydata(i,3)<=r3
           signal.inprice(k) = ceil(r3/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;
    elseif  daydata(i-1,3) >s1 && daydata(i,3)<=s1%% 波幅大于做空比
%         if (daydata(i,3) <= y_min - c && daydata(i-1,3) >  y_min - c) || (daydata(i,3) <=  y_min - c && daydata(i-1,3) <  y_min - c)
   
           k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = -1;         %% OUTPUT 3 -1
           if daydata(i,2)>=s1
           signal.inprice(k) = floor(s1/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;
    elseif daydata(i-1,3) >s2 && daydata(i,3)<=s2
           k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = +1;         %% OUTPUT 3 -1
           if daydata(i,2)>=s2
           signal.inprice(k) = floor(s2/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;
    elseif daydata(i-1,3) >s3 && daydata(i,3)<=s3
           k = k+1;
           signal.inplace(k) = i;         %% OUTPUT 2 
           signal.direct(k) = +1;         %% OUTPUT 3 -1
           if daydata(i,2)>=s3
           signal.inprice(k) = floor(s3/c)*c; %% OUTPUT 4
           else
            signal.inprice(k) = daydata(i,1);    
           end
           signal.break(k)= i;
    end
    
end    
end
%     if ~inpara{1}(6)  &&  k > 2  %% 一天内是否允许多次进场
%         break;
%     end

%% Step 3: 统计寻找到的信号 
if k > 0  
    signal.name = 'sr';  %% OUTPUT 1 
%      signal.inprice = daydata(signal.inplace,1);  %% OUTPUT 4
else
     signal = {}; 
end
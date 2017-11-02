function oper_info = handle_vol(todaydata, signal, outpara)

%%% 量价出场策略 (处理多个独立进场信号)
%%  配合成交量方法
%%% INPUT
%%  1 signal.name =     ''     STRING 
%%  2 signal.inplace =  []     VECTOR
%%  3 signal.direct  =  []     BOOL +1 or -1
%%  4 signal.inprcie =  []     VECTOR
%%  5 todaydata : data in today  [开盘价 最高价 最低价 收盘价]
%%  6 outpara =   [价格单位波动r 止损s 出现山形次数n 中间成交量的下限m]
%%
%%% OUTPUT
%%   1 oper_info.name     = signal.name 
%%   2 oper_info.inplace  = signal.inplace        
%%   3 oper_info.inprice  = signal.inprice 
%%   4 oper_info.direct   = signal.direct
%%   5 oper_info.outplace = 
%%   6 oper_info.outprice = 
%%   7 oper_info.profit   =   signal.outprice - signal.inprice (+1) or ---->   direct * (outprice - inprice) 
%%                          - signal.outprice + signal.inprice (-1)

%%% Step 0: INPUT check 
len_day = size(todaydata,1);  %% 多少行
r = outpara(1);  %% 价格单位波
s = outpara(2);  %% 止损
n = outpara(3);  %% 出现山形次数
m = outpara(4);  %% 中间成交量的下限


if isempty(signal)
   oper_info = {};  
   return;
else
   oper_info.name    = signal.name; 
   oper_info.inplace = signal.inplace; 
   oper_info.inprice = signal.inprice;  
   oper_info.direct  = signal.direct;   %% OUTPUT 1, 2, 3, 4 
  
end

%%% Step 1: Find the place to get out , OUTPUT 5, 6, 7
for i = 1:length(signal.inplace)
    k = 0;
    price_in = signal.inprice(i);
    p_in     = signal.inplace(i);

    if signal.direct(i) > 0                
       for j = p_in : len_day - 1
            
            if  j ~= p_in && price_in >= todaydata(j,1) + s       %% 1 开盘跳空止损出场  (进场点不用考虑开盘跳空问题)
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = todaydata(j,1) - price_in;  
                break; 
                
            elseif  price_in >= todaydata(j,3) + s   %% 2 止损出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in - s;
                oper_info.profit(i)   = - s;
                break;
                
            elseif  j ~= p_in && todaydata(j-1,2) < todaydata(j,2) && todaydata(j+1,2)>=todaydata(j,2) ...
                    && (j+1<=75|| 75<j-1<=133 || 135<j-1<173 || 175<j-1)...
                    && todaydata(j-1,5) < todaydata(j,5) && todaydata(j+1,5)>=todaydata(j,5) &&  todaydata(j,5) >=m    %% 3 寻找价格和成交量的山形
                k=k+1;
                if  k == n
                oper_info.outplace(i) = j + 2; 
                oper_info.outprice(i) = todaydata(j+2,1); 
                oper_info.profit(i)   = todaydata(j+2,1) - price_in; 
                break;
       
               end
               
            end
       end %% for j = p_in:len_dya
       if j == len_day - 1                                    %%  6 当日收盘出场 
                oper_info.outplace(i) = len_day; 
                oper_info.outprice(i) = todaydata(len_day,4); 
                oper_info.profit(i)   = todaydata(len_day,4) - price_in; 
       end
       
    elseif signal.direct(i)< 0      
        
       for j = p_in : len_day - 1
             
            if  j ~= p_in && todaydata(j,1) >= price_in + s       %% 1 开盘跳空止损出场   (进场点不用考虑开盘跳空问题)
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = price_in - todaydata(j,1);  
                
            elseif  todaydata(j,2) >= price_in + s   %% 2 止损出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in + s;
                oper_info.profit(i)   = - s;
                break;
                
            elseif  j ~= p_in && todaydata(j-1,3) > todaydata(j,2) && todaydata(j+1,3)<=todaydata(j,3) ...
                    && todaydata(j-1,5) < todaydata(j,5) && todaydata(j+1,5)>=todaydata(j,5) &&  todaydata(j,5) >=m    %% 3 寻找价格和成交量的山形
                k=k+1;
                if  k == n
                
                oper_info.outplace(i) = j + 2; 
                oper_info.outprice(i) = todaydata(j+2,1);  
                oper_info.profit(i)   = todaydata(j+2,1) - price_in; 
                break;
                
                end
            end
            
    
   
       if  j == len_day - 1                                  %%  6 当日收盘出场 
            oper_info.outplace(i) = len_day; 
            oper_info.outprice(i) = todaydata(len_day,4); 
            oper_info.profit(i)   =  price_in - todaydata(len_day,4); 
        end
    end  %% for j
    end%% if signal.direct > 0 or < 0
    
end  %% for i = 1:length(signal)
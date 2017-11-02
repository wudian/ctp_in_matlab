function oper_info = handle_touch_new(todaydata, signal, outpara)

%%% 橡胶价格突破出场策略
%%  两档回撤止盈方法
%%% INPUT
%%  1 signal.name =     ''     STRING 
%%  2 signal.inplace =  []     VECTOR
%%  3 signal.direct  =  []     BOOL +1 or -1
%%  4 signal.inprcie =  []     VECTOR
%%  5 todaydata : data in today  [开盘价 最高价 最低价 收盘价]
%%  6 outpara =   [价格单位波 止损 止盈触发点 回撤触发 回撤百分比]
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
u3 = outpara(3);  %% 止盈线
a = outpara(4);
b = outpara(5);

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
    price_in = signal.inprice(i);  %%入场价格
    p_in     = signal.inplace(i);  %%入场时间
    
    x = 0;
    j = p_in;
    
    if signal.direct(i) > 0
  
        for j = p_in:len_day-1    %% 从当根入场K线开始
            
            if  x == 0 && todaydata(j,4) - price_in >= u3 && todaydata(j-1,4) - price_in < u3
                x = 1;
            elseif x >= 1 && todaydata(j,2) - price_in >= u3 && todaydata(j-1,4) - price_in < u3
                x = x+1;
            end
            A = max(todaydata(p_in:j)) - price_in;
            B = todaydata(j+1,3) - price_in;
            if  j ~= p_in && price_in >= todaydata(j,1) + s       %% 1 开盘跳空止损出场
                oper_info.outplace(i) = j;
                oper_info.outprice(i) = todaydata(j,1);
                oper_info.profit(i)   = todaydata(j,1) - price_in;
                [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
                break;
                
            elseif  price_in >= todaydata(j,3) + s   %% 2 止损出场
                oper_info.outplace(i) = j;
                oper_info.outprice(i) = price_in - s;
                oper_info.profit(i)   = - s;
                [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
                break;
                
            elseif a <= A
                if todaydata(j+1,1) - price_in < b * A      %% 4.1  第一档 跳空回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = todaydata(j+1,1); 
                oper_info.profit(i)   = todaydata(j+1,1) - price_in;
                [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
                break;
               elseif B <= b * A                               %% 4.2  第一档 回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = price_in + r*floor(b*A/r);  
                oper_info.profit(i)   = r*floor(b * A/r);
                [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
                break;
               end
                
            elseif a > A && x >= 2 && todaydata(j,4) - price_in < u3 %%第二次打到止盈线
                oper_info.outplace(i) = j+1;   %%在下一根K线的开盘出场
                oper_info.outprice(i) = todaydata(j+1,1);
                oper_info.profit(i)   = todaydata(j+1,1) - price_in;
                [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
                break;
            end  %% 止损止盈
        end  %% for j = p_in+1:len_day-1
        
        if j == len_day-1                                    %%  6 当日收盘出场
            oper_info.outplace(i) = len_day;
            oper_info.outprice(i) = todaydata(len_day,4);
            oper_info.profit(i)   = todaydata(len_day,4) - price_in;
            [z,x] = max(todaydata(p_in:len_day,2));
                oper_info.bestprice(i) = z;
                [h,g] = min(todaydata(p_in:len_day,3));
                oper_info.badprice(i) = h;
        end
        
    elseif signal.direct(i)< 0
         
        for j = p_in:len_day-1
            
            if x == 0 && price_in - todaydata(j,4)> u3 && price_in - todaydata(j-1,4)< u3
               x = 1;
            elseif x >= 1 && price_in - todaydata(j,3)> u3 && price_in - todaydata(j-1,4)< u3
               x = x+1;
            end
              A = price_in - min(todaydata(p_in:j,3)); 
              B = price_in - todaydata(j+1,2);   
            if  j ~= p_in && todaydata(j,1) >= price_in + s       %% 1 开盘跳空止损出场
                oper_info.outplace(i) = j;
                oper_info.outprice(i) = todaydata(j,1);
                oper_info.profit(i)   = price_in - todaydata(j,1);
                [z,x] = min(todaydata(p_in:len_day,3));
                oper_info.bestprice(i) = z;
                [h,g] = max(todaydata(p_in:len_day,2));
                oper_info.badprice(i) = h;
                break;
                
            elseif  todaydata(j,2) >= price_in + s   %% 2 止损出场
                oper_info.outplace(i) = j;
                oper_info.outprice(i) = price_in + s;
                oper_info.profit(i)   = - s;
                [z,x] = min(todaydata(p_in:len_day,3));
                oper_info.bestprice(i) = z;
                [h,g] = max(todaydata(p_in:len_day,2));
                oper_info.badprice(i) = h;
                break;
                
            elseif a <= A
                if price_in  - todaydata(j+1,1) < b * A      %% 4.1  第一档 跳空回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = todaydata(j+1,1); 
                oper_info.profit(i)   = price_in - todaydata(j+1,1); 
                [z,x] = min(todaydata(p_in:len_day,3));
                oper_info.bestprice(i) = z;
                [h,g] = max(todaydata(p_in:len_day,2));
                oper_info.badprice(i) = h;
                break;
               elseif B <= b * A                               %% 4.2  第一档 回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = price_in - r*floor(b*A/r);  
                oper_info.profit(i)   = r*floor(b * A/r);
                [z,x] = min(todaydata(p_in:len_day,3));
                oper_info.bestprice(i) = z;
                [h,g] = max(todaydata(p_in:len_day,2));
                oper_info.badprice(i) = h;
                break;
               end
            elseif a > A && x >= 2 && price_in - todaydata(j,4) < u3 %%第二次打到止盈线
                oper_info.outplace(i) = j+1;   %%在下一根K线的开盘出场
                oper_info.outprice(i) = todaydata(j+1,1);
                oper_info.profit(i)   = price_in - todaydata(j+1,1);
                [z,x] = min(todaydata(p_in:len_day,3));
                oper_info.bestprice(i) = z;
                [h,g] = max(todaydata(p_in:len_day,2));
                oper_info.badprice(i) = h;
                break;    %% 止损止盈
            end    %% for j = p_in+1:len_day-1
        end   
        
    if  j == len_day-1                                  %%  6 当日收盘出场
        oper_info.outplace(i) = len_day;
        oper_info.outprice(i) = todaydata(len_day,4);
        oper_info.profit(i)   =  price_in - todaydata(len_day,4);
        [z,x] = min(todaydata(p_in:len_day,3));
        oper_info.bestprice(i) = z;
        [h,g] = max(todaydata(p_in:len_day,2));
        oper_info.badprice(i) = h;
    end
    
end   %% if signal.direct > 0 or < 0

end  %% for i = 1:length(signal)
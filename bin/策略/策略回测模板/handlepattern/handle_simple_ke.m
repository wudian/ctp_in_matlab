function oper_info = handle_simple_ke(todaydata, signal, outpara)

%%% 简单出场策略 (处理多个独立进场信号)
%%  两档回撤止盈方法
%%% INPUT
%%  1 signal.name =     ''     STRING 
%%  2 signal.inplace =  []     VECTOR
%%  3 signal.direct  =  []     BOOL +1 or -1
%%  4 signal.inprcie =  []     VECTOR
%%  5 todaydata : data in today  [开盘价 最高价 最低价 收盘价]
%%  6 outpara =   [价格单位波r 止损s 保单触发d 保单e 第一档浮盈触发p 第一档回撤百分比q 第二档浮盈触发u 第二档回撤百分比v 第三档回撤百分比w  凯斯特纳浮赢出场个数m ]
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
d = outpara(3);  %% 保单触发
e = outpara(4);  %% 保单
p = outpara(5);  %% 第一档浮盈触发
q = outpara(6);  %% 第一档回撤百分比
u = outpara(7);  %% 第二档浮盈触发
v = outpara(8);  %% 第二档回撤百分比
w = outpara(9);  %% 第三档浮盈触发
m=outpara(10);   %% 凯斯特纳浮赢出场个数m

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
    price_in = signal.inprice(i);
    p_in     = signal.inplace(i);

    if signal.direct(i) > 0                
       for j = p_in : len_day
              A = max(todaydata(p_in:j,2)) - price_in; 
              if j ~= len_day                                     %%  最小浮动盈利，搜索下一根
                 B = todaydata(j+1,3) - price_in;                 %% 最后一根选取当根，其余搜下根
                 lu2= todaydata(j+1,1);
              else
                 B  = todaydata(j,3) - price_in;
                 lu2= todaydata(j,1);
              end
                B1  = todaydata(j,3) - price_in;
              if j == p_in                                       %%  进场当根K线，不搜索止损
                 lu =todaydata(j+1,3);
              else
                 lu = todaydata(j,3) ;
              end
                             
            if  j ~= p_in && price_in >= todaydata(j,1) + s       %% 1 开盘跳空止损出场  (进场点不用考虑开盘跳空问题)
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = todaydata(j,1) - price_in;  
                break; 
                
            elseif  price_in >= lu + s   %% 2 止损出场
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in - s;
                oper_info.profit(i)   = - s;
                break;
                
            elseif  d <= A && A < p                   %% 3 保单触发 =< 浮盈 < 第一档止盈
               if  todaydata(j,2) - price_in < e       %% 3.1  保单跳空 出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = todaydata(j,1) - price_in; 
                break;
               elseif B1 <= e                           %% 3.2  保单出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in + e;  
                oper_info.profit(i)   = e; 
                break;
               end
              
             
            elseif  p <= A && A < u                   %% 4 第一档止盈 =< 浮盈 <  第二档止盈       
                                
                if lu2 - price_in < q * A      %% 4.1  第一档 跳空回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = lu2; 
                oper_info.profit(i)   = lu2 - price_in; 
                break;
               elseif B <= q * A                               %% 4.2  第一档 回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = price_in + r*floor(q*A/r);  
                oper_info.profit(i)   = r*floor(q * A/r);
                break;
               end
                
            elseif  u <= A                            %% 5 第一档止盈 =< 浮盈 <  第二档止盈       
               if lu2  - price_in < v * A       %% 5.1  第二档 跳空回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = lu2; 
                oper_info.profit(i)   = lu2 - price_in; 
                break;
               elseif B <= v * A                          %% 5.2  第二档 回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = price_in + r*floor(v * A/r);  
                oper_info.profit(i)   = r*floor(v * A/r);
                break;
               end
            elseif  w<=A      %% 5 第三档回撤止盈 
                 if  todaydata(j,4) <  sum(todaydata(j-m+1:j,3))/m  && todaydata(j-1,4) >= sum(todaydata(j-m:j-1,3))/m   %% 收盘价穿越下轨
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = lu2; 
                oper_info.profit(i)   = lu2 - price_in; 
                break;
                end
               
            end
       end %% for j = p_in:len_dya
       if j == len_day                                     %%  6 当日收盘出场 
                oper_info.outplace(i) = len_day; 
                oper_info.outprice(i) = todaydata(len_day,4); 
                oper_info.profit(i)   = todaydata(len_day,4) - price_in; 
       end
       
    elseif signal.direct(i)< 0      
        
       for j = p_in : len_day
              A = price_in - min(todaydata(p_in:j,3)); 
              if j ~= len_day                                %%  最小浮动盈利，搜索下一根
              B = price_in - todaydata(j+1,2);   
              lu2=todaydata(j+1,1);
              else
                  B = price_in - todaydata(j,2);
                  lu2=todaydata(j,1);
              end
              B1 = price_in - todaydata(j,2);
              if j == p_in                                  %%  开仓当根K线，不搜索止损，搜索下一根
                 lu= todaydata(j+1,2);
              else
                  lu= todaydata(j,2);
              end 
              
            if  j ~= p_in && todaydata(j,1) >= price_in + s       %% 1 开盘跳空止损出场   (进场点不用考虑开盘跳空问题)
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = price_in - todaydata(j,1);  
                
            elseif  lu >= price_in + s   %% 2 止损出场
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in + s;
                oper_info.profit(i)   = - s;
                break;
                
            elseif  d <= A && A < p                   %% 3 保单触发 =< 浮盈 < 第一档止盈
               if  price_in  - todaydata(j,3) < e       %% 3.1  保单跳空 出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = todaydata(j,1); 
                oper_info.profit(i)   = price_in - todaydata(j,1); 
                break;
               elseif B1 <= e                           %% 3.2  保单出场 
                oper_info.outplace(i) = j; 
                oper_info.outprice(i) = price_in - e;  
                oper_info.profit(i)   = e; 
                break;
               end
             
            elseif  p <= A && A < w                   %% 4 第一档止盈 =< 浮盈 <  第二档止盈       
               if price_in  - lu2 < q * A      %% 4.1  第一档 跳空回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = lu2; 
                oper_info.profit(i)   = price_in - lu2; 
                break;
               elseif B <= q * A                               %% 4.2  第一档 回撤止盈 出场 
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = price_in - r*floor(q*A/r);  
                oper_info.profit(i)   = r*floor(q * A/r);
                break;
               end
                
%             elseif  u <= A                            %% 5 第一档止盈 =< 浮盈 <  第二档止盈       
%                if lu2 - price_in < v * A       %% 5.1  第二档 跳空回撤止盈 出场 
%                 oper_info.outplace(i) = j+1; 
%                 oper_info.outprice(i) = lu2; 
%                 oper_info.profit(i)   = price_in - lu2; 
%                 break;
%                elseif B <= v * A                          %% 5.2  第二档 回撤止盈 出场 
%                 oper_info.outplace(i) = j+1; 
%                 oper_info.outprice(i) = price_in - r*floor(v * A/r);  
%                 oper_info.profit(i)   = r*floor(v * A/r);
%                 break;
%                end
            elseif  w<=A      %% 5 第三档回撤止盈 
              if  todaydata(j,4) >  sum(todaydata(j-m+1:j,2))/m && todaydata(j-1,4) <= sum(todaydata(j-m:j-1,2))/m   %% 收盘价穿越下轨
                oper_info.outplace(i) = j+1; 
                oper_info.outprice(i) = lu2; 
                oper_info.profit(i)   = price_in-lu2; 
                break;
                end
                 
            end %% for j 
       end
       if  j == len_day                                   %%  6 当日收盘出场 
            oper_info.outplace(i) = len_day; 
            oper_info.outprice(i) = todaydata(len_day,4); 
            oper_info.profit(i)   =  price_in - todaydata(len_day,4); 
        end
    end  %% for j
    end%% if signal.direct > 0 or < 0
    
end  %% for i = 1:length(signal)
    
    
 
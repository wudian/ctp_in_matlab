function record = strategy_weight(todaydata, oper_infos, para)
%%
%%% 解决对锁问题的权重策略：根据模型的权重解决对锁问题
%%  
%%% INPUT
%%  1 daydata   [开盘价 最高价 最低价 收盘价]
%%
%%  2 oper_infors{i}
%%  
%%          .name
%%          .inplace  =  []     VECTOR
%%          .direct   =  []     BOOL +1 or -1
%%          .inprcie  =  []     VECTOR
%%          .outplace =  []     VECTOR
%%          .outprice =  []     VECTOR
%%          .profit   =  []     NUMBER
%%
%%  3 strategy 
%%          .name = STRING    
%%          .para =  []       e.g.  'simple'  ， +1 or -1 or 0  
%%                            e.g.  'weight' 
%%                                       para{1} = [1 1 2 3];
%%                                       para{2} =  1
%%
%%% OUTPUT
%%  1 record
%%          .rec  = [inplace, inprice, outplace, outprice, direct, profit] 
%%          .name    (the name of the models for each record.)
%%          .weight  (the weight of the models for each record.)   
%%         

%%% Step 0: INPUT Check 
w = para{1};
w_matrix = zeros(length(w), length(w));
for i = 1:length(w)
    for j = 1:length(w)
        if w(i) && w(j)
           w_matrix(i,j) = w(i) - w(j);
        end
    end
end
record = {}; 

%%% Step 1: 计算每个模型对应的有几笔交易,将交易笔数不为零的模型信息 ---> oper_temp
n_model = length(oper_infos);    %% 模型数量 
if n_model == 0
   return;
end
if n_model ==1
    if ~isempty(oper_infos{1})
        for k = 1:length(oper_infos{1}.inplace)
        record.name{k} = oper_infos{1}.name;
        record.rec{k,1}  = [oper_infos{1}.inplace(k), oper_infos{1}.inprice(k), oper_infos{1}.outplace(k), oper_infos{1}.outprice(k), oper_infos{1}.direct(k), oper_infos{1}.profit(k)]; 
        end
    end
    return; 
end
len_day = size(todaydata,1); 
for i = 1:n_model
    if isempty(oper_infos{i})
       n_rec(i) = 0; 
       num_temp(i) = 0;
    else
       n_rec(i) = length(oper_infos{i}.inplace); %% 每个模型各自的交易数量，模型内部对锁问题已被先行解决。
       oper_temp{i} = oper_infos{i}; 
       num_temp(i) = n_rec(i); 
    end
end
n_temp = n_model; 

%%% Step 2: 不用寻找起始点，静态变量 dir 标识当前交易的方向
p_out = 0; %% 目前场内交易的最远出场点
dir = 0;

%%% Step 3: 处理对锁 %% i 当前时间点，j 当前模型序号，k 当前交易序号 （模型中的第k笔交易） 
r = 0;   

switch para{2}
  case 1
    for i = 1:len_day 
      for j = 1:n_temp       %% 第 j 个 模型的第 k 笔交易     
         for k = 1:num_temp(j)  %% oper_infos{j}.inplace(k)   
           if oper_temp{j}.inplace(k) == i          %% ！！按时间顺序进行处理，避免按模型顺序查找，导致时间点偏后的交易先进场                     
           %% 1 当前没有交易, 或交易刚结束  
             if oper_temp{j}.inplace(k) >= p_out       %% 当前交易结束掉的同一分钟 即可以入场 
              %% 交易入场  
                p_out  =  oper_temp{j}.outplace(k);
                dir =  oper_temp{j}.direct(k);
                r = r+1;        
                rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), direct, oper_temp{j}.profit(k)];  %% [inplace, inprice, outplace, outprice, direct, profit] 
                rec_name{r} = oper_temp{j}.name;  
                rec_weight(r) = para(j);  
                               
             %% 2 当前存在其它交易 （前面的strategy_single保证此交易不是本模型引入的，即单模型内部已没有对锁）
               elseif oper_temp{j}.inplace(k) < p_out 
               %% 2.1 同向加仓
                 if  oper_temp{j}.direct(k) * dir > 0                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                 %%  交易入场  
                   p_out  =  max([p_out oper_temp{j}.outplace(k)]);       %%  更新最长的出场点 
                   dir =  oper_temp{j}.direct(k);         %% 方向不变
                   r = r+1; 
                   rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), direct, oper_temp{j}.profit(k)]; 
                   rec_name{r} = oper_temp{j}.name;  
                   rec_weight(r) = para(j);  
                               
                   %% 2.2 反向则根据(1)权重和(2)简单策略判断是否反向开仓    
                    elseif oper_temp{j}.direct(k) * dir < 0  
                         if w(j) ~= 0      %% 2.2.1 判断本模型是否参与权重处理，如果本模型权重为零，就没有什么好操作的了。
                               sign  = 1;
                               for z = 1:r    %% 2.2.2 判断之前是否都是小权重模型，如果是，则当前信号不入场。        
                                 if  rec(z,3) > i  &&  rec(z,5) * oper_temp{j}.direct(k) < 0 && w_matrix(z,j) >= 0
                                   sign = 0; 
                                 end
                               end
                           if sign      %% 2.2.3 当前场内都是小权重模型，应该入场反转之。
                              for z = 1:r 
                               if  rec(z,3) > i  &&  rec(z,5) * oper_temp{j}.direct(k) < 0 && w_matrix(z,j) >= 0                             
                                   rec(z,3) = i;                                 %% outplace
                                   rec(z,4) = todaydata(i,4);                    %% outprice 
                                   rec(z,6) = (rec(z,4) - rec(z,2)) * rec(z,5);  %% profit =  (outprice - inprice) * direct   
                               end
                              end
                              r = r + 1; %% 2.2.4 反向开新仓 
                              p_out  =  oper_temp{j}.outplace(k);
                              rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), oper_temp{j}.direct(k), oper_temp{j}.profit(k)]; 
                              rec_name{r}= oper_temp{j}.name;   
                              rec_weight(r) = para(j);  
                              dir = oper_temp{j}.direct(k); 
                           end
                         end %% w(j)
                 end %%  oper_temp{j}.direct(k) * dir
           end %% if oper_temp{j}.inplace(k) >= p_out
         end %% oper_temp{j}.inplace(k) == i          %% 按时间顺序进行处理     
      end %% for k = 1:num_temp(j) 
    end  %% for j = 1:n_temp 
 end %% for i = 1:len_day   
        
 case 0   
     for i = 1:len_day 
         for j = 1:n_temp       %% 第 j 个 模型的第 k 笔交易   
             for k = 1:num_temp(j)  %% oper_infos{j}.inplace(k)    
                 if oper_temp{j}.inplace(k) == i          %% ！！按时间顺序进行处理，避免按模型顺序查找，导致时间点偏后的交易先进场！！
                 %% 1 当前没有交易 或 交易刚结束  
                      if oper_temp{j}.inplace(k) >= p_out   
                      %% 交易入场  
                          p_out  =  oper_temp{j}.outplace(k);
                          dir =  oper_temp{j}.direct(k);
                          r = r+1; 
                          rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), direct, oper_temp{j}.profit(k)]; %% [inplace, inprice, outplace, outprice, direct, profit]
                          rec_name{r}= oper_temp{j}.name; 
                          rec_weight(r) = para(j); 
                          
                  %% 2 当前存在其它交易 （前面的strategy_single保证此交易不是本模型引入的）
                     elseif oper_temp{j}.inplace(k) < p_out 
                       %% 2.1 同向加仓
                          if  oper_temp{j}.direct(k) * dir > 0        
                        %%  交易入场  
                            p_out  =  max([p_out oper_temp{j}.outplace(k)]);       %%  更新最长的出场点 
                            dir =  oper_temp{j}.direct(k);        %% 方向不变
                            r = r+1;    
                            rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), direct, oper_temp{j}.profit(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                            rec_name{r}= oper_temp{j}.name;  
                            rec_weight(r) = para(j);
                               
                       %% 2.2 反向则平正向仓，反向不加仓
                          elseif oper_temp{j}.direct(k) * dir < 0  
                            if w(j) == 0   
                          %%  2.2.1 统统平仓 
                              p_out  = i + 1;                            %%  更新出场点,下一个可以入场的点为 i+1; 
                              dir = 0;                                %%  没有方向,可以使下面的交易无法入场
                          %% 2.2.2 没有新的交易 但是要更新已有交易 调整出场点
                              r = size(rec,1);
                              for z = 1:r 
                                  if rec(z,3) > i && rec(z,5) * oper_temp{j}.direct(k) < 0
                                     rec(z,3) = i;                                 %% outplace
                                     rec(z,4) = todaydata(i,4);                    %% outprice 
                                     rec(z,6) = (rec(z,4) - rec(z,2)) * rec(z,5);  %% profit =  (outprice - inprice) * direct
                                   end
                               end
                            elseif w(j) >0
                                
                                
                                
                                
                            end%% w(j)
                          end %%  oper_temp{j}.direct(k) * dir
                     end %% if oper_temp{j}.inplace(k) >= p_out  
                   end %% oper_temp{j}.inplace(k) == i          %% 按时间顺序进行处理 
                end %% for k = 1:num_temp(j)
            end  %% for j = 1:n_temp 
        end %% for i = 1:len_day  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
              
%%% Step 4:     输出交易记录         
if r == 0
    record = {};
    return;
end
for y = 1:r
    record.name{y} = rec_name{y};            %%% OUTPUT
    record.rec{y,1} = rec(y,:);                %% 把记录都输出来，模型名称 操作 
end

%%% OUTPUT
%%  1 record
%%      .rec  = [inplace, inprice, outplace, outprice, direct, profit] 
%%      .name = ''   (which model deduces this record)              
        








        
          
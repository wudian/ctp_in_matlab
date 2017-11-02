function record = strategy_simple_ab(todaydata, oper_infos, para)
%%% 解决对锁问题的简单策略  (综合各独立进、出场信号)
%%  
%%% INPUT
%%  1 daydata   [开盘价 最高价 最低价 收盘价]
%%
%%  2 oper_infors{i} 
%%          .name
%%          .inplace  =  []     VECTOR
%%          .direct   =  []     BOOL +1 or -1
%%          .inprcie  =  []     VECTOR
%%          .outplace =  []     VECTOR
%%          .outprice =  []     VECTOR
%%  3 strategy 
%%          .name = STRING    
%%          .para =  []       e.g.  'simple'  ， +1 or -1 or 0  
%%% OUTPUT
%%  1 record
%%          .rec  = [inplace, inprice, outplace, outprice, direct, profit] 
%%          .name 
%%               (the name of the models for each record.)


%%% Step 0: INPUT Check 
l_lock = para; 
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
        record.rec{k,1}  = [oper_infos{1}.inplace(k), oper_infos{1}.inprice(k), oper_infos{1}.outplace(k), oper_infos{1}.outprice(k), ...
                               oper_infos{1}.direct(k), oper_infos{1}.profit(k),oper_infos{1}.bestprice(k), oper_infos{1}.badprice(k),oper_infos{1}.bestpricetime(k), ...
                               oper_infos{1}.badpricetime(k), oper_infos{1}.break(k),oper_infos{1}.goback(k), oper_infos{1}.gobacktime(k), oper_infos{1}.hisamp(k)]; 
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
       n_rec(i) = length(oper_infos{i}.inplace); %% 每个模型各自的交易数量
       if n_rec(i) > 1  %% 先解决模型内部对锁问题
%            在处理模型间对锁之前，把它处理掉 
             oper_temp{i} = oper_infos{i}; 
%            oper_temp{i_temp} = strategy_single(todaydata, oper_infos{i});
%            %% 涉及提前出场问题 
             num_temp(i) = length(oper_infos{i}.inplace); 
       else
            oper_temp{i} = oper_infos{i};  
            num_temp(i) = n_rec(i); 
       end
    end
end
n_temp = n_model; 
%%% Step 2: 不用寻找起始点，静态变量 direct 标识当前交易的方向
% current = zeros(n_temp,1) ; %% 第几个模型的第几笔交易在进行中 每个模型单独处理之后，这个变量就不需要了

p_out = 0; 
direct = 0; %% direct of records
r = 0;      %% number of records
%%% Step 3:     处理对锁 
%% i 当前时间点， j 当前模型序号， k 当前交易序号 （模型中）  
switch l_lock
    case 1    %% 同向加仓 反向不处理 
        for i = 1:len_day 
            for j = 1:n_temp       %% 第 j 个 模型的第 k 笔交易 
                for k = 1:num_temp(j)  %% oper_infos{j}.inplace(k)  
                   if oper_temp{j}.inplace(k) == i          %% ！！按时间顺序进行处理，避免按模型顺序查找，导致时间点偏后的交易先进场！！
                      %% 1 当前没有交易 或 交易刚结束 
                     if oper_temp{j}.inplace(k) >= p_out    
                          %% 交易入场  
                          p_out  =  oper_temp{j}.outplace(k);
                          direct =  oper_temp{j}.direct(k);
                          r = r+1; 
                          rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k),oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k),oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)];   %% [inplace, inprice, outplace, outprice, direct, profit] 
                          rec_name{r}= oper_temp{j}.name;  
                               
                        %% 2 当前存在其它交易 （前面的strategy_single保证此交易不是本模型引入的）
                     elseif oper_temp{j}.inplace(k) < p_out 
                           %% 2.1 同向加仓 反向不操作
                             if  oper_temp{j}.direct(k) * direct > 0        
                                %%  同向交易入场  
                                p_out  =  max([p_out oper_temp{j}.outplace(k)]);        %%  更新最长的出场点 
                                direct =  oper_temp{j}.direct(k);          %% 方向不变
                                r = r+1; 
                                rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;  
                              end
                     end
                   end %% oper_temp{j}.inplace(k) == i          %% 按时间顺序进行处理 
                end %% for k = 1:num_temp(j)
            end  %% for j = 1:n_temp 
        end %% for i = 1:len_day 
        
    case 0   %% 平正向仓，反向不开仓  
        for i = 1:len_day 
            for j = 1:n_temp       %% 第 j 个 模型的第 k 笔交易 
                for k = 1:num_temp(j)  %% oper_infos{j}.inplace(k)  
                   if oper_temp{j}.inplace(k) == i          %% ！！按时间顺序进行处理，避免按模型顺序查找，导致时间点偏后的交易先进场！！
                      %% 1 当前没有交易 或 交易刚结束  
                     if oper_temp{j}.inplace(k) >= p_out   
                         %% 交易入场  
                          p_out  =  oper_temp{j}.outplace(k);
                          direct =  oper_temp{j}.direct(k);
                          r = r+1; 
                          rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;                            
                          
                       %% 2 当前存在其它交易 （前面的strategy_single保证此交易不是本模型引入的）
                     elseif oper_temp{j}.inplace(k) < p_out 
                             %% 2.1 同向加仓
                             if  oper_temp{j}.direct(k) * direct > 0        
                                %%  交易入场  
                                p_out  =  max([p_out oper_temp{j}.outplace(k)]);       %%  更新最长的出场点 
                                direct =  oper_temp{j}.direct(k);        %% 方向不变
                                r = r+1;    
                               rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;                            
                               
                             %% 2.2 反向则平正向仓，反向不加仓
                             elseif oper_temp{j}.direct(k) * direct < 0  
                                %%  2.2.1 统统平仓 
                                p_out  = i + 1;                            %%  更新出场点,下一个可以入场的点为 i+1; 
                                direct = 0;                                %%  没有方向,可以使下面的交易无法入场
                                %% [inplace, inprice, outplace, outprice, direct,profit] 
                                %% 2.2.2 没有新的交易 但是要更新已有交易 调整出场点
                                r = size(rec,1);
                                for z = 1:r 
                                    if rec(z,3) > i 
                                        rec(z,3) = i;                                 %% outplace
                                        rec(z,4) = todaydata(i,4);                    %% outprice 
                                        rec(z,6) = (rec(z,4) - rec(z,2)) * rec(z,5);  %% profit =  (outprice - inprice) * direct
                                    end
                                end
                                %%  2.2.3 删除上面 在i点 已入场交易
                                del = find(rec(:,1) == i & rec(:,5)*direct > 0);
                                if length(del)
                                rec(del,:) = [];
                                rec_name(del) = [];
                                end
                                %%  2.2.4  更新记录数目
                                r = length(rec_name); 
                             end
                     end %% if oper_temp{j}.inplace(k) >= p_out  
                   end %% oper_temp{j}.inplace(k) == i          %% 按时间顺序进行处理 
                end %% for k = 1:num_temp(j)
            end  %% for j = 1:n_temp 
        end %% for i = 1:len_day 
          
    case -1  %% %% 平正向仓，反向开仓       
        l_change_direct = zeros(len_day,1);  % 在i点是否已经反向过了，只反向一次！ 
        for i = 1:len_day 
            for j = 1:n_temp       %% 第 j 个 模型的第 k 笔交易 
                for k = 1:num_temp(j)  %% oper_infos{j}.inplace(k)  
                   if oper_temp{j}.inplace(k) == i          %% ！！按时间顺序进行处理，避免按模型顺序查找，导致时间点偏后的交易先进场！！
                      %% 1 当前没有交易 或 交易刚结束  
                     if oper_temp{j}.inplace(k) >= p_out       %% 当前交易结束掉的同一分钟 即可以入场 
                          %% 交易入场  
                          p_out  =  oper_temp{j}.outplace(k);
                          direct =  oper_temp{j}.direct(k);
                          r = r+1; 
                             %% [inplace, inprice, outplace, outprice, direct, profit] 
                           rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;  
                               
                       %% 2 当前存在其它交易 （前面的strategy_single保证此交易不是本模型引入的）
                     elseif oper_temp{j}.inplace(k) < p_out 
                             %% 2.1 同向加仓
                             if  oper_temp{j}.direct(k) * direct > 0        
                             %%  交易入场  
                                p_out  =  max([p_out oper_temp{j}.outplace(k)]);       %%  更新最长的出场点 
                                direct =  oper_temp{j}.direct(k);         %% 方向不变
                                r = r+1; 
                              %% [inplace, inprice, outplace, outprice, direct,profit] 
                              rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;   
                               
                             %% 2.2 反向则平正向仓，反向开仓
                            elseif oper_temp{j}.direct(k) * direct < 0  
                              if ~l_change_direct(i)   %% 如果i点已经反向过，则不处理
                               %% 2.2.1 %%  更新出场点,下一个可以入场的点为 i,但是方向只能与反向之后的方向相同   
                                p_out  = i ;                            
                               %% 2.2.2 更新已有交易 调整出场点
                                r = size(rec,1); 
                                for z = 1:r 
                                    if  rec(z,3) > i   &&  rec(z,5) * direct > 0    %% 平仓 
                                        rec(z,3) = i;                                 %% outplace
                                        rec(z,4) = todaydata(i,4);                    %% outprice 
                                        rec(z,6) = (rec(z,4) - rec(z,2)) * rec(z,5);  %% profit =  (outprice - inprice) * direct
                                    end
                                end
                               %% 2.2.3  删除上面 在i点 已入场的原正向向交易
                                del = find(rec(:,1) == i);
                                if ~isempty(del)
                                rec(del,:) = [];
                                rec_name(del) = [];
                                end
                               %% 2.2.4 反向开新仓 
                                r = r + 1;
                                p_out  =  oper_temp{j}.outplace(k);
                                rec(r,:) = [oper_temp{j}.inplace(k), oper_temp{j}.inprice(k), oper_temp{j}.outplace(k), oper_temp{j}.outprice(k), ...
                                   direct, oper_temp{j}.profit(k),oper_temp{j}.bestprice(k), oper_temp{j}.badprice(k), oper_temp{j}.bestpricetime(k), oper_temp{j}.badpricetime(k), ...
                                   oper_temp{j}.break(k), oper_temp{j}.goback(k), oper_temp{j}.gobacktime(k), oper_infos{1}.hisamp(k)]; %% [inplace, inprice, outplace, outprice, direct,profit] 
                                rec_name{r}= oper_temp{j}.name;           
                               
                               %% 2.2.5 反向
                                direct = oper_temp{j}.direct(k); 
                                r = length(rec_name); 
                               
                              end %% if l_change_direct ==0
                             end
                              
                     end %% if oper_temp{j}.inplace(k) >= p_out
                   end %% oper_temp{j}.inplace(k) == i          %% 按时间顺序进行处理 
                   
                end %% for k = 1:num_temp(j)
            end  %% for j = 1:n_temp 
        end %% for i = 1:len_day   
        
        otherwise 
        disp('Parameters for strategy_simple are not defined yet');       
end
              
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
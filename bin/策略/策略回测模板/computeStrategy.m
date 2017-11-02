%% computeStrategy.m 计算策略的进场和出场信号
%%  models;%%% 可以很多model一起放进来run，data-driven programming method is used here
           %%    How to get in :   models parameters  
           %%   models{i}           %% several models in one;    
           %%    1 models{i}.name      (model_name)   STRING  
           %%               e.g. 'tcdtci', 'price_break', 'amp_break'， 'fix_time'         
           %%
           %%    2 models{i}.inpara    (model_parameter)  
           %%       models{i}.inpara{1}  =  [连发次数 采样频率 止损点 保单触发 保单] (parameters)
           %%       models{i}.inpara{2}  =  [1 75 135 175 215]
           %%       (sec_points)
           %%      e.g. 'tcdtci'     [连发次数 采样频率 止损点 保单触发 保单]
           %%           'price_break' [间隔时间 滑点 收盘前n分钟不操作]
           %%           'amp_break'   [做多比 做空比 波幅 价格最小波动 收盘前n分钟不操作]
           %%           'fix_time'    [时间窗口 做多比 做空比 滑点 收盘前n分钟不操作]    
           %%    
           %%    3 models{i}.outpara    (out_parameter)
           %%       models{i}.outpara{1}  = '出场策略' 
           %%       models{i}.outpara{2}  = [参数1 参数2 参数3 ... ... ] 
           %%         e.g. 'simple'    [价格单位波 止损 保单触发 保单 第一档浮盈触发 第一档回撤百分比
           %%                                    第二档浮盈触发 第二档回撤百分比]
           %%
           %%     Different model has different paremeters 
           %%     foreach model, [p_in direct] pattern_info = find_pattern(daydata,models);
           %%                           p_out  = handle_pattern();
           
%% strategy %%    How to deal with collision, and get out
           %%   
           %%    strategy.name = 'simple', 'by_model', ''
           %%    strategy.para = [];   e.g.   'simple'  +1 -1 or 0
           
tic; 
      
%% Step 1: In everyday data (n_day)
% disp('Step 1: In everyday data (n_day)')
for i=1:n_day
    if i==1
        ATR(i)=max(all_daydata{i}(:,2))-min(all_daydata{i}(:,3));
    else
        ATR(i)= max([max(all_daydata{i}(:,2))-min(all_daydata{i}(:,3)),abs(max(all_daydata{i}(:,2))-all_daydata{i-1}(data.sec_point(end),4)),abs(min(all_daydata{i}(:,3))-all_daydata{i-1}(data.sec_point(end),4))]);
    end    
end
global i_day 
for i_day = 1:n_day        %%n_day 
    model_info = ['正在进行第 ', num2str(i_day), '次循环计算']   ;
    disp(model_info);
%%% load yesterday and today 's data
   daydata = all_daydata{i_day};  
   if i_day == 1
       hisdata = daydata; 
   else
       hisdata = all_daydata{i_day-1}; 
   end
% day_info = ['fsys is dealing with the data in ' num2str(i_day), '-th day']   ;
% disp(day_info)   

%% Step 2 :  Find every in points signals of everydata              (Where to get in)
%% signals{i}   (one signal = one_pattern) 
%%  1 signals{i}.name    = 'tcdtci', 'price_break', 'amp_break'， 'fix_time' 
%%  2 signals{i}.inplace    = [all_place ... ];   %% where to get in
%%  3 signals{i}.direct  = [1 -1 +1 ... ];   %% +1 : Buy;  -1 : Sell
%%  4 signals{i}.inprice = [ ]
%%
% disp('Step 2 :  Find every in points signals of everydata ')
clear signals
%% 2.1 initial search
if i_day<=n_day
signals = find_pattern(hisdata, daydata, models, ATR, i_day);      %% signals for i_day
else
     for j = 1:length(models)
         models{j}.inpara{2} = data.sec_pointnew;
     end
signals = find_pattern(hisdata, daydata, models, ATR, i_day);      %% signals for i_day     
end
if i_day ==1
    for j = 1:length(signals)
        if length(signals{j})
        switch signals{j}.name  %%  第一天不做波幅突破和价格突破
            case {'amp_break', 'fix_time', 'open', 'sr'}
                signals{j} = {};     
            otherwise
        end
                
        end
    end
end


all_signals{i_day} = signals; 
%%  Step 3 :  Deal with the signals, and output operation information (Where to get out)
%%  oper_info{i}           %%   
%%    1 oper_info{i}.name = models{i}.outpara{1}   STRING  
%%               e.g. 'simple', 'tcdtci' ... ...             
%%    2 oper_info{i}.inplace  =          VECTOR
%%    3 oper_info{i}.inprice  =          VECTOR
%%    4 oper_info{i}.outplace =          VECTOR
%%    5 oper_info{i}.outprice =          VECTOR
%%    6 oper_info{i}.profit   =          VECTOR
% disp('Step 3 :  Deal with the signals, and output operation information (Where to get out)')
clear oper_infos
oper_infos = handle_pattern(daydata, signals, models);   %% operation information for i_day
for i_info = 1:length(oper_infos)
    oper_new{i_info} = strategy_single(daydata,oper_infos{i_info});
end

%%  Step 4 :  Solve the anti-lock problem 
%  disp('Step 4 :  Solve the anti-lock problem ')
rec_sys1{i_day} = handle_strategy(daydata, oper_new, strategy);  %% 解决对锁问题 / 也适用于单模型

end 
%% Step 5 : Write the records to EXCEL tables
disp('Step 5 : Write the records to EXCEL tables')
outfile =['.\sys_result\' num2str(i_run)-2 '.xls']; 
stas = write_records(rec_sys1, len_day,dateTime, outfile, per, factor, fee, l_print, 60, n_day);
t0 = toc; 






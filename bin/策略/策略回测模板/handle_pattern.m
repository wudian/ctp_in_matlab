function oper_infos = handle_pattern(todaydata, signals, models)
%%% 
%%  To handle various patterns 
%%   oper_info{i}   <------>   models{i}.outpara{1} = 'simple' ... 出场策略名称
%%                             models{i}.outpara{2} = [   ]        出场策略参数
%%     1 oper_infos{i}.name = models{i}.name 
%%     2 oper_infos{i}.inplace  = [ ]          (where to get in) 
%%     3 oper_infos{i}.inprice  = [+1 or -1]   (+1  Buy; -1 Sell)
%%     4 oper_infos{i}.outplace = [ ]
%%     5 oper_infos{i}.outprice = [ ]
%%     6 oper_infos{i}.profit   = [ ]
%%    models
%%      .outpara{1} = 'simple'    (策略名称)
%%      .outpara{2} =   [价格单位波r 止损s 保单触发d 保单e 第一档浮盈触发p 第一档回撤百分比q 第二档浮盈触发u
%%    第二档回撤百分比v]

 func_name = 'handle_pattern';
 current_path = which(func_name);
 current_path = current_path(1:end - (length(func_name) + 2));
 func_path = [current_path, 'handlepattern', '\'];
 addpath(func_path);
 
 if isempty(signals)
     oper_infos = {};
     return; 
 end
 
for i = 1:length(models)
    
    switch models{i}.outpara{1}
         
        case 'simple' %% 两档回扯止盈出场
            oper_infos{i} = handle_simple(todaydata, signals{i}, models{i}.outpara{2});
            
        case 'simple_ab' %% 两档回扯止盈出场
            oper_infos{i} = handle_simple_ab(todaydata, signals{i}, models{i}.outpara{2});    
            
        case 'simple_2' %% 止盈出场
            oper_infos{i} = handle_simple_2(todaydata, signals{i}, models{i}.outpara{2});
            
        case 'simple_lastmin' %% 止盈出场
            oper_infos{i} = handle_simple_lastmin(todaydata, signals{i}, models{i}.outpara{2});    
            
        case 'simple_closeconfirm' %% 两档回扯止盈出场
            oper_infos{i} = handle_simple_closeconfirm(todaydata, signals{i}, models{i}.outpara{2});   
            
        case 'simple_turtlesoup' %% 两档回扯止盈出场
            oper_infos{i} = handle_simple_turtlesoup(todaydata, signals{i}, models{i}.outpara{2});    
            
        case 'dynamic' %% 两档回扯止盈出场
            oper_infos{i} = handle_dynamic(todaydata, signals{i}, models{i}.outpara{2});    
            
        case 'simpvol' %% 两档回扯止盈出场
            oper_infos{i} = handle_simvol(todaydata, signals{i}, models{i}.outpara{2});
            
       case 'simple_1' %% 两档回扯止盈出场
            oper_infos{i} = handle_simple_1(todaydata, signals{i}, models{i}.outpara{2});     
            
        case 'volume'  %% 量出场    
            oper_infos{i} = handle_vol(todaydata, signals{i}, models{i}.outpara{2});
            
       case 'simple_vol'  %% 量价出场    
            oper_infos{i} = handle_simple_vol(todaydata, signals{i}, models{i}.outpara{2});     
            
       case 'simvol'  %% 量价出场    
            oper_infos{i} = handle_simvol(todaydata, signals{i}, models{i}.outpara{2}); 
            
       case 'simple_ke'  %% 量价出场    
            oper_infos{i} = handle_simple_ke(todaydata, signals{i}, models{i}.outpara{2}); 
       
        case 'touch_1' %% 两档回扯止盈出场
            oper_infos{i} = handle_touch_1(todaydata, signals{i}, models{i}.outpara{2});     
       
         case 'simple_endchange' %% 两档回扯止盈出场,收盘出场精确到分钟
            oper_infos{i} = handle_simple_endchange(todaydata, signals{i}, models{i}.outpara{2});     
           
        otherwise 
            
            
            
    end
end


 rmpath(func_path);


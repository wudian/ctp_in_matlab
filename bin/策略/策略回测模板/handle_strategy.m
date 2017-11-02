function record = handle_strategy(daydata, oper_infos, strategy)
%%% 
%%  To handle various models and solve the anti-lock problem
%%   record   <------>  reasonrable records for oper_infos
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
%%          .rec  = [inplace, inprice, outplace, outprice, direct, profit, volume, i_day] 
%%          .name 
%%               the name of the models for each record.
 func_name = 'handle_pattern';
 current_path = which(func_name);
 current_path = current_path(1:end - (length(func_name) + 2));
 func_path = [current_path, 'strategy', '\'];
 addpath(func_path);
 
 switch strategy.name
        case 'simple'
            record = strategy_simple(daydata, oper_infos, strategy.para);
            
       case 'simple_ab'
            record = strategy_simple_ab(daydata, oper_infos, strategy.para);  
       
       case 'signalout'
            record = strategy_signalout(daydata, oper_infos); 
            
       case 'signalout_2'
            record = strategy_signalout_2(daydata, oper_infos);      
            
            
        case 'weight'    
            record = strategy_weight(daydata, oper_infos, strategy.para);
            
        case ''
            
        otherwise 
                  
 end
     
     
rmpath(func_path);





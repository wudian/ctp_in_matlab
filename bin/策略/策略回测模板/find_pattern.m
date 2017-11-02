function signals = find_pattern(hisdata,todaydata, models, ATR, day)
%%% 
%% INPUT
%%   1 models
%%      .outpara{1} = 'simple'    (策略名称)
%%      .outpara{2} =   [价格单位波r 止损s 保单触发d 保单e 第一档浮盈触发p 第一档回撤百分比q 第二档浮盈触发u
%%    To find various patterns 
%%   signals{i}   <------>   models{i} 
%% OUTPUT 
%%     1 signals{i}.name = models{i}.name 
%%     2 signals{i}.inplace = [ ]          (where to get in) 
%%     3 signals{i}.direct =  [+1 or -1]   (+1  Buy; -1 Sell)
%%     4 signals{i}.inprice = [ ]


 func_name = 'find_pattern';
 current_path = which(func_name);
 current_path = current_path(1:end - (length(func_name) + 2));
 func_path = [current_path, 'findpattern', '\'];
 addpath(func_path);

 for i = 1:length(models)
    switch models{i}.name 
     case 'tcdtci'       %% n连发
         signals{i} = find_tcdtci(todaydata,models{i}.inpara); 
         
      case 'boll4'       %% n连发
         signals{i} = find_boll4(hisdata,todaydata,models{i}.inpara);     
         
     case 'sr'       %% n连发
         signals{i} = find_sr(hisdata,todaydata,models{i}.inpara); 
         
     case 'atr'       %% n连发
         signals{i} = find_atr(todaydata,models{i}.inpara);
         
     case '4q'       %% n连发
         signals{i} = find_4q(todaydata,models{i}.inpara);     
         
    case 'rangebreakout'       %% n连发
         signals{i} = find_rangebreakout(todaydata,models{i}.inpara);     
         
     case 'mv'       %% n连发
         signals{i} = find_mv(todaydata,models{i}.inpara);     
         
      case 'price_break_2se'       %% n连发
         signals{i} = find_pb_2se(hisdata,todaydata,models{i}.inpara);      
         
     case  'ncucd'       %% n连阴 n连阳
         signals{i} = find_ncucd(todaydata,models{i}.inpara); 
         
     case  'out'
         signals{i} = find_out(todaydata,models{i}.inpara);
         
     case  'fmi'
         signals{i} = find_fmi(todaydata,models{i}.inpara);    
         
     case 'price_break'  %% 价格突破
         signals{i} = find_pb(todaydata,models{i}.inpara);
         
      case 'price_break_original'  %% 价格突破
         signals{i} = find_pb_original(hisdata,todaydata,models{i}.inpara); 
         
      case 'halfday_break'  %% 价格突破
         signals{i} = find_halfday_break(hisdata,todaydata,models{i}.inpara);     
         
    case 'price_break_atr'  %% 价格突破
         signals{i} = find_pb_atr(todaydata,models{i}.inpara,ATR, day);      
         
    case 'price_break_open'  %% 价格突破
         signals{i} = find_pb_open(todaydata,models{i}.inpara);      
         
    case 'boll'  %% 价格突破
         signals{i} = find_boll(todaydata,models{i}.inpara);      
         
     case 'price_break_forgettime'  %% 价格突破
         signals{i} = find_pb_forgettime(todaydata,models{i}.inpara);
         
     case 'price_break_goback'  %% 价格突破
         signals{i} = find_pb_goback(todaydata,models{i}.inpara);    
         
     case 'turtlesoup'  %% 价格突破
         signals{i} = find_turtlesoup(todaydata,models{i}.inpara); 
  
     case 'amp_break'    %% 波幅突破
         signals{i} = find_ab(hisdata,todaydata,models{i}.inpara); 
         
    case 'open'    %% 开盘模型
         signals{i} = find_open(hisdata,todaydata,models{i}.inpara);     
         
     case 'fix_time'     %% 固定时间突破
         signals{i} = find_ft(hisdata,todaydata,models{i}.inpara); 
         
     case 'fix_time_1'     %% 固定时间突破
         signals{i} = find_ft_1(hisdata,todaydata,models{i}.inpara); 
         
      case 'fix_time_atr'     %% 固定时间突破
         signals{i} = find_ft_atr(hisdata,todaydata,models{i}.inpara,ATR, day);     
    
     case 'supp_resis'   %% 支撑阻力
         signals{i} = find_supris(hisdata,todaydata,models{i}.inpara); 
         
     case 'measure'      %% 小节
         signals{i} = find_measure(todaydata,models{i}.inpara);
         
     case 'halfday'      %% 小节
         signals{i} = find_halfday(todaydata,models{i}.inpara);    
         
     case 'measure1'      %% 小节
         signals{i} = find_measure1(todaydata,models{i}.inpara);    
        
     case 'overleap_break' %% 跳空突破
         signals{i} = find_overleap(hisdata,todaydata,models{i}.inpara);   
         
      case 'outinfo' %% 外盘比价
         signals{i} = find_outinfo(hisdata,todaydata,models{i}.inpara);          
         
      case 'tcdtci_vol'  %% 考虑成交量因素的n连发模型
         signals{i} = find_tcdtci_vol(todaydata,models{i}.inpara);             
                  
      case 'tcdtci_amp'  %% 考虑幅度的n连发模型 (设定上下限参数)
         signals{i} = find_tcdtci_amp(todaydata,models{i}.inpara);       
         
        case 'measure_obv'  %% 考虑成交量因素的分钟OBV + 小节模型
            signals{i} = find_measure_obv(todaydata,models{i}.inpara);
        
        case 'tcdtci_obv'  %% 考虑obv的n连发模型 (设定上下限参数)
         signals{i} = find_tcdtci_obv(todaydata,models{i}.inpara);  
         
         case 'kconfig'  %% 考虑obv的n连发模型 (设定上下限参数)
         signals{i} = find_kconfig(todaydata,models{i}.inpara); 
         
         case 'kconfig_1'  %% 考虑obv的n连发模型 (设定上下限参数)
         signals{i} = find_kconfig_1(todaydata,models{i}.inpara); 
         
         case 'price_break_obv'  %% 考虑obv的突破模型 (设定上下限参数)
         signals{i} = find_pb_obv(todaydata,models{i}.inpara);
         
         case 'fix_time_obv'  %% 考虑obv的突破模型 (设定上下限参数)
         signals{i} = find_ft_obv(todaydata,models{i}.inpara);
            
        case 'hdli'  %% 跌中高和涨中低
         signals{i} = find_hdli(todaydata,models{i}.inpara);
         
        case 'kestner'  %% 跌中高和涨中低
         signals{i} = find_kestner(todaydata,models{i}.inpara);  
        case '4candle' %%练习策略4连发
         signals{i} = find_4candle(todaydata,models{i}.inpara);    
         
     otherwise
         signals{i} = [ 'pattern: ', models{i}.name, ' is not defined yet.']; 
    end
  end
        
 rmpath(func_path);

         
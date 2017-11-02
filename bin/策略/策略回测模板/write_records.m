function [stas suc mes] = write_records(record, len_day, dateTime, filename, per, factor, fee, l_print, n, unchange)

%% 通过raw_data查时间；通过intable查日期
%%% INPUT
%%   1  record{i_day}
%%         .name{i} = ''         e.g.   model name
%%         .rec{i}  = []         [inplace, inprice, outplace, outprice, direct,profit] 
%%   2 len_day
%%   3 in_table 
%%   4 filename
%%   5 per = [12 6 3 1 2]      分割比例 [月 月 月 月 周]
%%   6 factor = 每点金额
%%   7 fee = 每手手续费
%%   8 l_print: 是否打印（1：是；0：否）

output{1,1} = '日期'; output{1,2} = '进场时间';  output{1,3} = '进场价格';  output{1,4} = '出场时间';  output{1,5} = '出场价格';
output{1,6}= '方向'; output{1,7}= '盈利值';  output{1,8}= '最大浮盈价'; output{1,9}= '最大浮亏价'; output{1,10}= '进场k线'; output{1,11}= '出场k线';
output{1,12}= '模型名称';  output{1,13}= '月份'; output{1,14}= '星期'; output{1,15}= '最大浮盈价时间'; output{1,16}= '最大浮亏价时间';
output{1,17}= '前极点时间';  output{1,18}= '极点之后最大回撤点'; output{1,19}= '极点之后最大回撤点时间';  output{1,20}= '波幅';

disp('开始进入写入模块')

i = 1; 

for j = 1:length(record)
    if ~length(record{j})

        continue;
    end
   m=min(length(record{j}.rec),n);
    for k = 1:m
%         if isempty(record{j}.rec{k})
%             continue;
%         end
        i = i + 1; 
        if j<=unchange
%         output{i,1} = intable{(j-1)*len_day + 2, 1};   %% 进场日期
          output{i,1}=dateTime{1,1}{(j-1)*len_day + 2, 1};   %% 进场日期
           t1 = record{j}.rec{k}(1) + (j-1) * len_day + 1;
           t2 = record{j}.rec{k}(3) + (j-1) * len_day + 1;
        else
%          output{i,1} = intable{unchange*len_day+(j-unchange-1)*225 + 2, 1};   %% 进场日期
           output{i,1} = dateTime{1,1}{unchange*len_day+(j-unchange-1)*225 + 2, 1};   %% 进场日期
           t1 = record{j}.rec{k}(1) + unchange*len_day+(j-unchange-1)*225 + 1;
           t2 = record{j}.rec{k}(3) + unchange*len_day+(j-unchange-1)*225 + 1; 
        end
           
%         output{i,2} = intable{t1,2};      %% 进场时间 
          output{i,2} = dateTime{1,2}{t1,1};     %% 进场时间 
        output{i,3} = record{j}.rec{k}(2);%% 进场价格
        
%         output{i,4} = intable{t2,2};      %% 出场时间
          output{i,4} = dateTime{1,2}{t2,1};      %% 出场时间
        output{i,5} = record{j}.rec{k}(4);%% 出场价格
        
        if record{j}.rec{k}(5) > 0
        output{i,6} = 1;                %% 方向 ： B +1   S -1
        else
        output{i,6} = -1;                %% 方向 ： B +1   S -1
        end   
        output{i,7} = record{j}.rec{k}(6) * factor - fee;%% 净盈利金额
        output{i,8} = record{j}.rec{k}(7);  %% 最大浮盈价
        output{i,9} = record{j}.rec{k}(8);%% 最大浮亏价
        output{i,12} = record{j}.name{k};  %% 模型名称
        output{i,10} = record{j}.rec{k}(1);%% 进场k线
        output{i,11} = record{j}.rec{k}(3);%% 出场k线
        output{i,13} = month(output{i,1});   %% 月份
        output{i,14} = weeknum(output{i,1}); %% 星期
        output{i,15} = record{j}.rec{k}(9);%% 最大浮盈价时间
        output{i,16} = record{j}.rec{k}(10);%% 最大浮亏价时间
%         output{i,17} = record{j}.rec{k}(11);   %% 前极点时间
%         output{i,18} = record{j}.rec{k}(12); %% 极点之后最大回撤点
%         output{i,19} = record{j}.rec{k}(13); %% 极点之后最大回撤点时间
%          output{i,20} = record{j}.rec{k}(14); %% 昨日波幅
    end
end

if l_print
    [suc mes] = xlswrite(filename,output); 
end

n_record = i;

i_month = 0;
for i = 2:n_record-1
    if  output{i,13} ~= output{i+1,13}
        i_month = i_month + 1;
        mon(i_month,1) = i;  
    end
end
i_month = i_month + 1; 
mon(i_month,1) = n_record;

i_week = 0;
for i = 2:n_record-1
    if  output{i,14} ~= output{i+1,14}
        i_week = i_week + 1;
        week(i_week,1) = i;  
    end
end
i_week = i_week + 1;
week(i_week,1) = n_record;


%% 全部记录
iw = 0; il = 0; sw = 0; sl = 0; 
for j = 2:n_record
    if output{j,7} >= 0 
        iw = iw + 1;  sw = sw + output{j,7};
    elseif output{j,7} < 0
        il = il + 1;  sl = sl + output{j,7};
    end
end

%% per(1)  eg.,12个月
iw_1 = 0; il_1 = 0; sw_1 = 0; sl_1 = 0;
if i_month > per(1)
i_month_temp = i_month - per(1);
else
 i_month_temp = 1;  
end
n_temp = mon(i_month_temp,1); 
for j = (n_temp + 1):n_record
    if output{j,7} >= 0 
        iw_1 = iw_1 + 1;  sw_1 = sw_1 + output{j,7};
    elseif output{j,7} < 0
        il_1 = il_1 + 1;  sl_1 = sl_1 + output{j,7};
    end
end

%% per(2)  eg.,6个月
iw_2 = 0; il_2 = 0; sw_2 = 0; sl_2 = 0;
if i_month > per(2)
i_month_temp = i_month - per(2);
else
 i_month_temp = 1;  
end
n_temp = mon(i_month_temp,1);
for j = (n_temp + 1):n_record
    if output{j,7} >= 0 
        iw_2 = iw_2 + 1;  sw_2 = sw_2 + output{j,7};
    elseif output{j,7} < 0
        il_2 = il_2 + 1;  sl_2 = sl_2 + output{j,7};
    end
end

%% per(3)  eg.,3个月
iw_3 = 0; il_3 = 0; sw_3 = 0; sl_3 = 0;
if i_month > per(3)
i_month_temp = i_month - per(3);
else
i_month_temp = 1;
end
    

n_temp = mon(i_month_temp,1); 
for j = (n_temp + 1):n_record
    if output{j,7} >= 0 
        iw_3 = iw_3 + 1;  sw_3 = sw_3 + output{j,7};
    elseif output{j,7} < 0
        il_3 = il_3 + 1;  sl_3 = sl_3 + output{j,7};
    end
end

%% per(4)  eg.,1个月
iw_4 = 0; il_4 = 0; sw_4 = 0; sl_4 = 0;
if  i_month > per(4)
i_month_temp = i_month - per(4);
else
i_month_temp = 1; 
end
n_temp = mon(i_month_temp,1); 
for j = (n_temp + 1):n_record
    if output{j,7} >= 0 
        iw_4 = iw_4 + 1;  sw_4 = sw_4 + output{j,7};
    elseif output{j,7} < 0
        il_4 = il_4 + 1;  sl_4 = sl_4 + output{j,7};
    end
end

%% per(5): eg.,2周
iw_5 = 0; il_5 = 0; sw_5 = 0; sl_5 = 0;
if i_week > per(5)
i_week_temp = i_week - per(5);
else
i_week_temp = 1;  
end
n_temp = week(i_week_temp,1); 
for j = (n_temp + 1):n_record
    if output{j,7} >= 0 
        iw_5 = iw_5 + 1;  sw_5 = sw_5 + output{j,7};
    elseif output{j,7} < 0
        il_5 = il_5 + 1;  sl_5 = sl_5 + output{j,7};
    end
end

stas = [iw sw il sl i_month iw_1 sw_1 il_1 sl_1 per(1)  iw_2 sw_2 il_2 sl_2 per(2) iw_3 sw_3 il_3 sl_3 per(3)...
     iw_4 sw_4 il_4 sl_4 per(4) iw_5 sw_5 il_5 sl_5 per(5)/4]; 

   
        
        
        
        
        
        
        







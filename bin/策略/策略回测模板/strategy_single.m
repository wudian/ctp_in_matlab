function oper_new = strategy_single(todaydata, oper_info)

%%% INPUT
%%  1 daydata   [开盘价 最高价 最低价 收盘价]
%%
%%  2 oper_info 
%%          .name
%%          .inplace  =  []     VECTOR     %% 升序排列 
%%          .direct   =  []     BOOL +1 or -1
%%          .inprice  =  []     VECTOR
%%          .outplace =  []     VECTOR
%%          .outprice =  []     VECTOR
%%          .profit   =  []

%%% OUTUPT
%%   oper_new 
%%          .name
%%          .inplace  =  []     VECTOR
%%          .direct   =  []     BOOL +1 or -1
%%          .inprice  =  []     VECTOR
%%          .outplace =  []     VECTOR
%%          .outprice =  []     VECTOR
%%          .profit   =  []

oper_new = oper_info; 
if length(oper_info) == 0
    return;
end

%% may be a problem
if length(oper_info.inplace) <=1
    return;
end
del = []; 
n = length(oper_info.inplace) ;
for i = 1 : n-1
      for j = 1 : i 
         %% 同一模型当前交易与当前未完成交易反向，则必然平仓
         if ismember(j,del)
             continue;
         end
         if  oper_new.direct(j) * oper_new.direct(i+1) < 0  &&  oper_new.outplace(j) >= oper_new.inplace(i+1) &&  oper_new.inplace(j) <= oper_new.inplace(i+1)
                    del = union(del, i+1);

         elseif oper_new.direct(j) * oper_new.direct(i+1) > 0  %% 同向不开新仓
                 if  oper_new.inplace(i+1) >= oper_new.inplace(j)  &&  oper_new.inplace(i+1) <= oper_new.outplace(j) 
                     del = union(del, i+1);
                 elseif oper_new.inplace(j) >= oper_new.inplace(i+1) && oper_new.inplace(j) <= oper_new.outplace(i+1) 
                     del = union(del, j);
                 end
         end
      end
end
%%
if length(del) %% 删除模型内 同向开仓的交易 
%     oper_new.name;
    oper_new.inplace(del)  =  [];
    oper_new.direct(del)    =  [];
    oper_new.inprice(del)   =  [];
    oper_new.outplace(del)  =  [];
    oper_new.outprice(del)  =  [];   
    oper_new.profit(del)  =  [];
    oper_new.bestprice(del)  =  [];   
    oper_new.bestpricetime(del)  =  [];   
    oper_new.badprice(del)  =  [];
    oper_new.badpricetime(del)  =  [];
%     oper_new.break(del)=[];
%     oper_new.goback(del)  =  [];
%     oper_new.gobacktime(del)=[];
    return;
end
%%    
    
    
    
















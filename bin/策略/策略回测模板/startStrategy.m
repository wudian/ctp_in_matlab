%% main.m 回测模块主函数 ，该模块进行参数的定义和变量的声明
%% 预备知识  商品一天有225根BAR， 股指一天有270根BAR
clear;clc;tic;    
disp('一、加载数据')
%%
addpath('DATA')
data.sec_point = [1, 75, 135, 175,270]; %% 一天有多少个一分钟的bar
data.sec_pointnew = [1,75, 135,270];
per = [12 6 3 1 2];      %% 分割比例 [月 月 月 月 周]
factor =300; %% 每点金额
fee =80;  %% 每手手续费金额
deposit = 100000; %% 保证金
l_print =1; %%是否调试
disp('进场参数定义')
%%
initime=30 ;%开始交易时间
slipe =0.2  ;%滑点
endtime=5  ;%结束交易时间
maxtime = 3 ;%交易次数
disp('出场参数定义')
%%
    minmove =0.2; %最小跳动
    stoploss =12; %止损点位
    sp1 =9  ;%保本触发点
    pp1 =0.1   ;%保本金额
    sp2 =18   ;%一级止盈点
    pp2 =0.2   ;%一级回测比例
    sp3 =60   ;%二级止盈点
    pp3 =0.6  ; %二级回测比例

disp('二、读取数据')
%%
load('data.mat')
% load('IF000.mat')
len_day = data.sec_point(end); %一天有多少根bar 
n_day = size(raw_data,1)/len_day;%%交易天数
disp('三、保存每天的价格数据')
%%
for i =1:n_day  
 all_daydata{i} = raw_data(len_day*(i-1)+1:len_day*(i-1) + len_day,:); 
end

disp('四、OUTPUT 统计表头')
%%
if ~exist('sys_result','dir')
mkdir sys_result ;
end 
output{1,1} = '模型-参数 统计表';  
output{2,1} = 'model 1'; output{2,2}= 'model 2'; output{2,3}= 'model 3';   output{2,4}= 'model 4';
output{2,5} = '总交易次数'; output{2,6} = '总胜率'; output{2,7} = '平均盈亏比'; output{2,8} = '净盈利额'; output{2,9} = '折合月率'; 
output{2,10} = [num2str(per(1)) '个月交易次数']; output{2,11} = [num2str(per(1)) '个月胜率']; output{2,12} = [num2str(per(1)) '个月平均盈亏比'];
output{2,13} = [num2str(per(1)) '个月净盈利额']; output{2,14} = [num2str(per(1)) '个月折合月率']; 
output{2,15} = [num2str(per(2)) '个月交易次数']; output{2,16} = [num2str(per(2)) '个月胜率']; output{2,17} = [num2str(per(2)) '个月平均盈亏比'];
output{2,18} = [num2str(per(2)) '个月净盈利额']; output{2,19} = [num2str(per(2)) '个月折合月率']; 
output{2,20} = [num2str(per(3)) '个月交易次数']; output{2,21} = [num2str(per(3)) '个月胜率']; output{2,22} = [num2str(per(3)) '个月平均盈亏比'];
output{2,23} = [num2str(per(3)) '个月净盈利额']; output{2,24} = [num2str(per(3)) '个月折合月率'];
output{2,25} = [num2str(per(4)) '个月交易次数']; output{2,26} = [num2str(per(4)) '个月胜率']; output{2,27} = [num2str(per(4)) '个月平均盈亏比'];
output{2,28} = [num2str(per(4)) '个月净盈利额']; output{2,29} = [num2str(per(4)) '个月折合月率'];
output{2,30} = [num2str(per(5)) '周交易次数']; output{2,31} = [num2str(per(5)) '周胜率']; output{2,32} = [num2str(per(5)) '周平均盈亏比'];
output{2,33} = [num2str(per(5)) '周净盈利额']; output{2,34} = [num2str(per(5)) '周折合月率'];
i_run = 2; 
disp('五、模型进场模块和策略绩效输出模块')
        %% 参数循环优化设置
%          for initime = 30:1:30
%              for endtime =5:1:5
%                  for slipe = 1:1:1
%                      for maxtime =3:1:3
%                          for stoploss = 17:1:17
%                              for sp1 =17:1:17
%                                  for pp1 = 5:1:5
%                                      for sp2 = 35:1:35
%                                          for pp2 = 0.4:0.1:0.4
%                                              for sp3 = 90:1:90
%                                                  for pp3 =0.6:0.1:06
clear models
i_run = i_run + 1;
model_info = ['fsys is dealing with ', num2str(i_run-2), '-th parameters group']   ;
disp(model_info);

models{1}.name = '4candle'; % 运用的策略名称
models{1}.inpara{1} = [initime slipe endtime 0 150];           %%  'price_break' [间隔时间t 滑点c 收盘前n分钟不操作 一天最多操作次数 前波幅下限]
models{1}.inpara{2} = data.sec_point;
models{1}.outpara{1} = 'simple'; 
models{1}.outpara{2} =[minmove stoploss sp1 pp1 sp2 pp2 sp3 pp3 1];   %%[价格单位波 止损  保单触发 保单  第一档浮盈触发 第一档回撤百分比 第二档浮盈触发 第二档回撤百分比]

disp('5.1 : strategy 对锁策略')
%%
strategy.name = 'simple';
strategy.para = 0;  %% -1:平，开； 0：平，不开； 1：不平，不开

disp('5.2: 计算策略的进场和出场，进行标记')
%%
computeStrategy; 

disp('5.3:出场参数进行输出')
if ~isempty(models)
%% fix_time   [时间窗口 做多波幅过滤 做空波幅过滤 滑点 收盘前n分钟不操作 做多次数上限 做空次数上限]
output{i_run,1} = [models{1}.name ' : ' num2str(models{1}.inpara{1}(1)) ' ' num2str(models{1}.inpara{1}(2))  ' ' num2str(models{1}.inpara{1}(3)) ' ' num2str(models{1}.inpara{1}(4)) ' ' num2str(models{1}.inpara{1}(5))...%% ' ' num2str(models{1}.inpara{1}(6))  ' ' num2str(models{1}.inpara{1}(7))...%%  ' ' num2str(models{1}.inpara{1}(8)) ...
                     ' ' num2str(models{1}.outpara{2}(1)) ' ' num2str(models{1}.outpara{2}(2)) ' ' num2str(models{1}.outpara{2}(3)) ' ' num2str(models{1}.outpara{2}(4)) ' ' num2str(models{1}.outpara{2}(5)) ' ' num2str(models{1}.outpara{2}(6))...
                     ' ' num2str(models{1}.outpara{2}(7)) ' ' num2str(models{1}.outpara{2}(8))];
end

if length(models) > 1
output{i_run,2} = [models{2}.name ' : '  num2str(models{2}.inpara{1}(1)) ' ' num2str(models{2}.inpara{1}(2)) ' ' num2str(models{2}.inpara{1}(3))...
                   ' ' num2str(models{2}.outpara{2}(1)) ' ' num2str(models{2}.outpara{2}(2)) ' ' num2str(models{2}.outpara{2}(3)) ' ' num2str(models{2}.outpara{2}(4))...
                    ' ' num2str(models{2}.outpara{2}(5)) ' ' num2str(models{2}.outpara{2}(6)) ' ' num2str(models{2}.outpara{2}(7)) ' ' num2str(models{2}.outpara{2}(8))];
%                      ' ' num2str(models{2}.outpara{2}(9)) ' ' num2str(models{2}.outpara{2}(10)) ];   
end

if length(models) > 2
output{i_run,3} = [models{3}.name ' : '  num2str(models{3}.inpara{1}(1)) ' ' num2str(models{3}.inpara{1}(2)) ' ' num2str(models{3}.inpara{1}(3)) ' ' num2str(models{3}.inpara{1}(4)) ...      
                     ' ' num2str(models{3}.outpara{2}(1)) ' ' num2str(models{3}.outpara{2}(2)) ' ' num2str(models{3}.outpara{2}(3)) ' ' num2str(models{3}.outpara{2}(4))...
                    ' ' num2str(models{3}.outpara{2}(5)) ' ' num2str(models{3}.outpara{2}(6)) ' ' num2str(models{3}.outpara{2}(7)) ' ' num2str(models{3}.outpara{2}(8))];      
end

if length(models) > 3
output{i_run,4} = [models{4}.name ' : '  num2str(models{4}.inpara{1}(1)) ' ' num2str(models{4}.inpara{1}(2)) ' ' num2str(models{4}.inpara{1}(3)) ' ' num2str(models{4}.inpara{1}(4)) ...      
                    num2str(models{4}.inpara{1}(5))];  
end


for i_c = 1:length(per)+1
    trades(i_c) = stas(1+5*(i_c-1))+stas(3+5*(i_c-1)); 
    P(i_c) = stas(1+5*(i_c-1))/trades(i_c) ; 
    A(i_c) = - ( stas(2+5*(i_c-1))/stas(1+5*(i_c-1)) ) / ( stas(4+5*(i_c-1))/stas(3+5*(i_c-1)) ); 
    Profit(i_c) = stas(2+5*(i_c-1)) + stas(4+5*(i_c-1));
    kelly = max(0,((1 + A(1)) * P(1) - 1)/A(1));
    ProPer(i_c) = Profit(i_c)/ stas(5+5*(i_c-1)) / deposit * kelly;
end

for i_c = 1:6
    output{i_run,0+5*i_c} = trades(i_c);
    output{i_run,1+5*i_c} = P(i_c);
    output{i_run,2+5*i_c} = A(i_c);
    output{i_run,3+5*i_c} = Profit(i_c);
    output{i_run,4+5*i_c} = ProPer(i_c);
end
%                                                  end %%pp3
%                                              end %%sp3
%                                          end %%pp2
%                                      end %%sp2
%                                  end %%pp1
%                              end %%sp1
%                          end %%stoploss
%                      end %%maxtime
%                  end %%slipe
%              end %%endtime
%          end %%initime
%          

disp('六、OUTPUT 统计表内容')
%%
xlswrite('.\sys_result\交易绩效\股指绩效.xls',output);
rmpath('DATA')
toc;














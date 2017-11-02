function [PDI, MDI, DX, ADX, ADXR] = DMI_General(Open,High,Low,Close,N,M,options)
% DMI:Directioal Movement Index 趋向指标（动向指标）实现
% DMI是由发明RSI的技术分析大师J·W·Wilder发明的，是判断股价走向的实用性的技术分析工具。
% DMI一共包括±DI、DX、ADX和ADXR四项内容。 
% by liyang 2013/08/05
% farutoliyang@gmail.com
% Input:
%       Open,High,Low,Close,N,M,options
% Output:
%       PDI, MDI, DX, ADX, ADXR
%% 输入参数检查设置
if nargin < 7
    options = 1;
end
if nargin < 6
    M = 6;
end
if nargin < 5
    N = 14;
end
%% 初始化
MaxLen = numel(Open);

PDI = zeros(MaxLen, 1);
MDI = zeros(MaxLen, 1);
DX = zeros(MaxLen, 1);
ADX = zeros(MaxLen, 1);
ADXR = zeros(MaxLen, 1);

TR = zeros(MaxLen, 1);
TR_temp = zeros(MaxLen, 1);

HD = zeros(MaxLen, 1);
LD = zeros(MaxLen, 1);

DMP = zeros(MaxLen, 1);
DMM = zeros(MaxLen, 1);
DMP_temp = zeros(MaxLen, 1);
DMM_temp = zeros(MaxLen, 1);

%% 
if 1 == options
    for i = 1:MaxLen
        if i > 1
            TR_temp(i) = ...
                max( [High(i)-Low(i), abs(High(i)-Close(i-1)), abs(Low(i)-Close(i-1))] );
            HD(i) = High(i) - High(i-1);
            LD(i) = Low(i-1) - Low(i);
        end
        if HD(i)>0 && HD(i)>LD(i)
            DMP_temp(i) = HD(i);
        end
        if LD(i)>0 && LD(i)>HD(i)
            DMM_temp(i) = LD(i);
        end
    end
    
    for i = 1:MaxLen
        if i >= N 
            TR(i) = nansum( TR_temp(i-N+1:i) );
            DMP(i) = nansum( DMP_temp(i-N+1:i) );
            DMM(i) = nansum( DMM_temp(i-N+1:i) );
        end
    end
    
    PDI = DMP*100./TR;
    MDI = DMM*100./TR;
    DX = abs(PDI-MDI)./(PDI+MDI)*100;
    
    for i = 1:MaxLen
        if i >= M
            ADX(i) = nanmean( DX(i-M+1:i) );          
        end
        if i > M
            ADXR(i) = ( ADX(i)+ADX(i-M) )/2;
        end
    end    
    
    PDI( 1:(max(N,M)-1) ) = nan;
    MDI( 1:(max(N,M)-1) ) = nan;
    DX( 1:(max(N,M)-1) ) = nan;
    ADX( 1:(max(N,M)-1) ) = nan;
    ADXR( 1:(max(N,M)-1) ) = nan;
end
%%
if 2 == options

    
    
    
    
    
    
    
end

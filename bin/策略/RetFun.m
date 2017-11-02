function [ret,lret,cost] = RetFun( bp, sp, bs, Num, Lots)
%% 白银现货收益率计算（除去成本）
% 双向收费，开仓平仓都收取；
% 单向手续费是万八；
% 点差8个点；
% 递延费是万二
%%成本举例：
% 现货白银：
%      保证金 ：   4.6×15,000×1×8% =5520元 
%       交易手续费  建仓时： 4.6×15,000×1×0.8‰ = 55.2元 
%                    平仓时： 7×15,000×1×0.8‰ = 84元 
%       延期费：    4.6×15,000×1×0.2‰×3（天） = 41.4元 
% 点差：固定8个点。（120元）
% 递延费的天数为自然日，超过凌晨4点就算1天

%ret为收益率,lret为盈利金额
if nargin<3
    bs=ones(size(bp)); %默认为买入，卖空bs=-1
end

if nargin<4
    Num=ones(size(bp));
end

if nargin<5
    Lots=ones(size(bp));
end


St=15; %1标准手为15KG
Lev=12.5; %杠杆12.5倍
Fee=0.08/100; %手续费万八，双向收取
Def=0.02/100* Num; %递延费万二乘以天数
Spe=8*15*Lots; %1手点差为8个点，即120元
costFee=(sp*Fee+bp*Fee)*St.*Lots;
costDef=bp.*Def*St.*Lots;
cost=[costFee;costDef;Spe];

% ret=((sp-bp)*St.*Lots.*bs-(sp*Fee+bp*Fee+bp.*Def)*St.*Lots-Spe)./(bp*St.*Lots)*Lev;
ret=((sp-bp)*St*bs)/(bp*St*Lots)*Lev;
lret=(sp-bp)*St.*Lots.*bs-(sp*Fee+bp*Fee+bp.*Def)*St.*Lots-Spe;

end


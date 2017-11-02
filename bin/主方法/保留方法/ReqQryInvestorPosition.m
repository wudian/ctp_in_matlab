function  ReqQryInvestorPosition(Instrument)
%查询投资者持仓。分多仓和空仓两种，有总仓位、可用仓、昨开仓、今开仓、今开可用仓、仓位均价等
% <param name="instrument" type="char">合约代码:不填-查所有</param>

%举例： 
% ReqQryInvestorPosition('IF1406')
% ReqQryInvestorPosition('IF1406; IF1409')
% ReqQryInvestorPosition('')

    global td;
    if nargin<1 || strcmp(Instrument, '')
        td.ReqQryInvestorPosition('');
        return;
    end

    instruments = strrep(Instrument, ',', ' ');
    instruments = strrep(instruments, ';', ' ');

    [first, rest] = strtok(instruments);
    while ~strcmp(first, '')
        td.ReqQryInvestorPosition(first);
        [first, rest] = strtok(rest);
    end
    
end


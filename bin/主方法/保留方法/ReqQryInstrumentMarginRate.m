function ReqQryInstrumentMarginRate(Instrument)
%请求查询合约保证金率
% <param name="Instrument">合约代码：用','或';'隔开</param>

%举例： 
% ReqQryInstrumentMarginRate('IF1406')
% ReqQryInstrumentMarginRate('IF1406, IF1409')

    global td;
    if nargin<1 || strcmp(Instrument, '')
        td.ReqQryInstrumentMarginRate('',  QuantBox.CSharp2CTP.TThostFtdcHedgeFlagType.Speculation); %不起作用
        return;
    end
    
    instruments = strrep(Instrument, ',', ' ');
    instruments = strrep(instruments, ';', ' ');

    [first, rest] = strtok(instruments);
    while ~strcmp(first, '')
        td.ReqQryInstrumentMarginRate(first,  QuantBox.CSharp2CTP.TThostFtdcHedgeFlagType.Speculation);
        [first, rest] = strtok(rest);
    end

end

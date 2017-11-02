function  ReqQryInstrumentCommissionRate(Instrument)
%请求查询合约手续费率
% <param name="Instrument">合约代码：用','或'；'隔开</param>

%举例： 
% ReqQryInstrumentCommissionRate('IF1406')
% ReqQryInstrumentCommissionRate('IF1406, IF1409')
    
    global td;
    if nargin<1 || strcmp(Instrument, '')
        td.ReqQryInstrumentCommissionRate(''); %不起作用
        return;
    end
    
    instruments = strrep(Instrument, ',', ' ');
    instruments = strrep(instruments, ';', ' ');

    [first, rest] = strtok(instruments);
    while ~strcmp(first, '')
        td.ReqQryInstrumentCommissionRate(first);
        [first, rest] = strtok(rest);
    end

end


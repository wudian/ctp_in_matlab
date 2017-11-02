function  OnRspQryInstrument( ~, arg )
%查询合约响应

if arg.pRspInfo.ErrorID ~= 0
    str = sprintf('查询合约%s失败：%s', char(arg.pInstrument.InstrumentID), char(arg.pRspInfo.ErrorMsg));
    disp(str);
    return;
end

global AllInstruments;
AllInstruments{size(AllInstruments, 2) + 1} = char(arg.pInstrument.InstrumentID);

global KLineOfAllInstruments;
KLineOfAllInstruments = setfield(KLineOfAllInstruments, char(arg.pInstrument.InstrumentID), {});

global VolumeMultiple;
VolumeMultiple = setfield(VolumeMultiple, char(arg.pInstrument.InstrumentID), arg.pInstrument.VolumeMultiple);

end

function OnTdDisconnect(~,arg)
% 与TD断开的回调

str = sprintf('与TD断开,当前连接状态(%s),错误代码(%d),错误信息(%s)', char(arg.step), arg.pRspInfo.ErrorID, char(arg.pRspInfo.ErrorMsg));
disp(str);

end

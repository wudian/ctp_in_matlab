function OnMdDisconnect(~, arg)
% 行情断线回报
str = sprintf('与MD断开,当前连接状态(%s),错误代码(%d),错误信息(%s)', char(arg.step), arg.pRspInfo.ErrorID, char(arg.pRspInfo.ErrorMsg));
disp(str);

end

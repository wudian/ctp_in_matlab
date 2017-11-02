function OnTdConnect(sender,arg)
% 交易连接回报

% 交易状态到Confirmed就表示登录并确认成功
if arg.result == QuantBox.CSharp2CTP.ConnectionStatus.Logined
    %% 初始化全局变量
    Types;
    ReqQryDepthMarketData();
    disp('成功登录交易服务器')
end

end

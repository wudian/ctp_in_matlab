function OnMdConnect(~, arg)

% 行情状态到Logined就表示登录成功
if arg.result == QuantBoxCSharp.ConnectionStatus.Logined
    disp('成功登录行情服务器');
end

end

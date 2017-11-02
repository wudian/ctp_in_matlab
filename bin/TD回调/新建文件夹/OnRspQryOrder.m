function  OnRspQryOrder( ~, arg )
%查委托响应

if arg.pRspInfo.ErrorID == 0
    str = sprintf('合约在交易所的代码(%s)交易所代码(%s)报单编号(%s)报单提交状态(%s)报单状态(%s)状态信息(%s)', char(arg.pOrder.ExchangeInstID), char(arg.pOrder.ExchangeID), char(arg.pOrder.OrderSysID), char(arg.pOrder.OrderSubmitStatus), char(arg.pOrder.OrderStatus), char(arg.pOrder.StatusMsg));
    disp(str);
    if arg.bIsLast == true
        disp('查询委托完成'); 
    end
else
    str = sprintf('查委托失败:%s', char(arg.pRspInfo.ErrorMsg));
    disp(str);
end

end


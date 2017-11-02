from QuantBox import *
ReadConfigFile("F:\\CTP-MATLAB\\bin\\ConfigFile.xml")
md = CMdUserApi()
td = CTraderApi()
md.Connect()
td.Connect()


md.Subscribe('IF1407')

import sys
import time
sys.path.append(r'F:\CTP-MATLAB\bin')
import os
os.chdir(r'F:\CTP-MATLAB\bin')
import clr
from System import *
clr.AddReference('QuantBox.CSharp2CTP')
from QuantBox.CSharp2CTP import *
from QuantBox.CSharp2CTP.Event import *
from System import *

if1409_price = 0.0;

CommApi.CTP_ReadConfigFile("F:\\CTP-MATLAB\\bin\\ConfigFile.xml");

def OnMdConnect(md, e):   print e.result
def OnMdRtnDepthMarketData_Tick(md, e):
    print e.pTick.InstrumentID, e.pTick.ExchangeTime

def OnTdConnect(md, e):   print e.result

md = MdApiWrapper()
td = TraderApiWrapper()
md.OnConnect += OnMdConnect
md.OnRtnDepthMarketData_Tick += OnMdRtnDepthMarketData_Tick
td.OnConnect += OnTdConnect

md.Connect();                      
td.Connect();
while True:pass

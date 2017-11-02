%% Integrating MATLAB with QuickFIX/J
% This example illustrates the steps involved in integrating MATLAB and
% QuickFIX/J
%
%  Copyright 2012 The MathWorks, Inc.

%% Add QuickFIX/J files to java path
% First the JAR files need to on the java class path.  Add them to
% classpath.txt then restart MATLAB.
type classpath.txt

%% Add the JAR file onto the path
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-all-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-core-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-examples-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix40-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix41-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix42-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix43-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix44-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fix50-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\quickfixj-msg-fixt11-1.5.2.jar');
javaaddpath('C:\sandbox\java\quickfixj\lib\mina-core-1.1.7.jar');
javaclasspath

%% Load in the relevant pacakages
import quickfix.*
import quickfix.examples.banzai.*
import quickfix.examples.banzai.ui.*

%% Start up Banzai
% Set up in MATLAB the example application, Banzai.  This is a order entry
% interface.
settings = SessionSettings('banzai.cfg');
storeFactory = FileStoreFactory(settings);
logFactory = ScreenLogFactory(true,true,true,true);
messageFactory = DefaultMessageFactory();
orderTable = OrderTableModel;
execTable = ExecutionTableModel;
application = BanzaiApplication(orderTable,execTable);
initiator = SocketInitiator(application,storeFactory,settings,logFactory,messageFactory);
frame = BanzaiFrame(orderTable,execTable,application);

%% Take a look at initiator methods
% Note there is a start and stop method.  This will set up communication to
% a FIX system.
methods(initiator)

%% Start the FIX Execution Engine
system('C:\sandbox\java\quickfixj\bin\executor.bat&')

%% Connect to Execution Engine
% Establish communications between Execution Engine and Order Entry
% application.
initiator.start

%% Review Order Methods
methods(orderTable)

%% Get the first order
% Note there needs to be an order placed in Banzai.  If one does not exist,
% create one.
o = orderTable.getOrder(0)

%% Sending Orders
% In Banzai app, requires two steps.  The first is to add it to the table
% (for record keeping), and then send it to the FIX Execution Engine using
% the applicaiton.send method.
orderTable.addOrder(o)
application.send(o);

%% Creating a Custom Order
% To create a new order, we need to create an Banzai Order Object.
o = Order
methods(Order)
%%
% This is a Buy order for a new security, MW.
FIX = initiator.getSessions
o.setSessionID(FIX.get(2))
o.setSymbol('MW')
o.setQuantity(50)
o.setOpen(o.getQuantity)
orderTable.addOrder(o)
application.send(o)

%% A Sell Order
o = Order
FIX = initiator.getSessions;
o.setSessionID(FIX.get(2));
o.setSymbol('MW');
o.setQuantity(50);
o.setOpen(o.getQuantity)
orderSide = OrderSide.parse('Sell');
o.setSide(orderSide);

orderTable.addOrder(o)
application.send(o);
%% Shut down the session
initiator.stop


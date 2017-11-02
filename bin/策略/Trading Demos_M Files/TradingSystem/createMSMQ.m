function q = createMSMQ()

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
%% Add the Assembly for MSMQ
NET.addAssembly('System.Messaging');

%% Create the Queue (if it doesn't already exist)
if ~(System.Messaging.MessageQueue.Exists('.\private$\seminarQ'))
    q = System.Messaging.MessageQueue.Create('.\private$\seminarQ');
end

%% Connect to the queue
q = System.Messaging.MessageQueue('.\private$\seminarQ');

% Change the formatting to ActiveX so Excel can parse the messages
ax = System.Messaging.ActiveXMessageFormatter;
q.Formatter = ax;


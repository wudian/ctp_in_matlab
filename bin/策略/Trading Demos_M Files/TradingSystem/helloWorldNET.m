%% Utilize .NET Objects in MATLAB
% This is a simple demonstration to highlight making use of .NET Assemblies directly
% in MATLAB.

% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
%% Our current location
seminarCity = 'Toronto';

%% Add the .NET assembly we are going to need
NET.addAssembly('System.Speech');

%% Create and use a SpeechSynthesizer object 
% set the rate and volume properties and call the speak method
speaker = System.Speech.Synthesis.SpeechSynthesizer();
speaker.Rate = 1;
speaker.Volume = 100;
speaker.Speak(['Hello, ', seminarCity, '!']);
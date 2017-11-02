%% README.m
% DISCLAIMER: THE SAMPLE FILES ENCLOSED IN THIS DOWNLOAD ARE FOR
% ILLUSTRATION PURPOSES ONLY.  USE THE INFORMATION CONTAINED IN THIS
% DOWNLOAD AT YOUR OWN RISK.
%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
%% General information
% The files contained in this dowload were used in the webinar titled:
% _Algorithmic Trading with MATLAB Products for Financial Applications_
% that originally aired on November 18, 2010.  You can watch an archived
% version of this webinar from http://www.mathworks.com/webinars and look
% for the title webinar.  It is recomended you watch this webinar as you
% walk through the code.

%% What you need to run these files
% These files were developed and tested on R2010b.  The products need to
% run all of the files are:
%
%  * MATLAB
%  * Statistics Toolbox
%  * Optimization Toolbox
%  * Global Optimization Toolbox
%  * Financial Toolbox
%  * Real-Time Workshop (and Simulink)
license('inuse')

%% What's NOT included in this download
% Files generated from <AlgoTradingDemo5.html AlgoTradingDemo5.m> such as
% the moving average MEX file and all files generated using the emlc
% command (the C-Code source files).  You will need Real-Time Workshop to
% generate these files.
%
% Also not inlcuded is the powerpoint slides.  You can find these on the
% registration page for the webinar.

%% Demos
%
% * Demo 1: Moving averages (<AlgoTradingDemo1.html html>, <matlab:open('AlgoTradingDemo1.m') MATLAB Script>)
% * Demo 2: RSI and moving average (<AlgoTradingDemo3.html html>, <matlab:open('AlgoTradingDemo2.m') MATLAB Script>
% * Demo 3: Evolutionary learning (<AlgoTradi2gDemo3.html html>, <matlab:open('AlgoTradingDemo3.m') MATLAB Script>
% * Demo 4: Adding Williams %R to the mix (<AlgoTradingDemo4.html html>, <matlab:open('AlgoTradingDemo4.m') MATLAB Script>
% * Demo 5: Profiling and C-Code generation (<AlgoTradingDemo5.html html>, <matlab:open('AlgoTradingDemo5.m') MATLAB Script>
dir('Algo*')

%% Published files
% HTML formated versions with results for each demo can be found in the
% _html_ folder.
dir('html\*.html')
%% MATLAB Code
% Listing of the MATLAB code files.  You can open this files in the editor
% and step through them using cell mode.
dir('*.m')
%%
% and the genetic programming files
dir('gaFiles\')
%% Data files
% The data files (daily and 1 minute)
dir('Bund*')
%%
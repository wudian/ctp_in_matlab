function varargout = regressionBasketGUI(varargin)
% REGRESSIONBASKETGUI MATLAB code for regressionBasketGUI.fig
%      REGRESSIONBASKETGUI, by itself, creates a new REGRESSIONBASKETGUI or raises the existing
%      singleton*.
%
%      H = REGRESSIONBASKETGUI returns the handle to a new REGRESSIONBASKETGUI or the handle to
%      the existing singleton*.
%
%      REGRESSIONBASKETGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in REGRESSIONBASKETGUI.M with the given input arguments.
%
%      REGRESSIONBASKETGUI('Property','Value',...) creates a new REGRESSIONBASKETGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before regressionBasketGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to regressionBasketGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help regressionBasketGUI

% Last Modified by GUIDE v2.5 03-May-2013 17:15:55

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @regressionBasketGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @regressionBasketGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before regressionBasketGUI is made visible.
function regressionBasketGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to regressionBasketGUI (see VARARGIN)

% Choose default command line output for regressionBasketGUI
handles.output = hObject;

% Set default parameters
params.numDays = 15;
params.movAvgWindow   = 20;  % Length of the window for MA and STD
params.stdDevWindow   = 20;
params.openPosition   = 1.5; % open positions at mean +2 sigma
params.closePosition  = 1; % close positions mean +1 sigma
params.stopLoss       = 5;   % stop loss at +3 sigma
params.holdingPeriod  = 6; 
handles.params = params;

paramGrid.numDays       = [15 60 15];
paramGrid.movAvgWindow  = [20 60 20];
paramGrid.openPosition  = [1 2 0.5];
paramGrid.closePosition = [0 1 0.5];
paramGrid.stopLoss      = [3 5 1];
paramGrid.holdingPeriod = [6 20 4];
handles.paramGrid       = paramGrid;

handles.contractSpec = [];

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes regressionBasketGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = regressionBasketGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in SelectTarget.
function SelectTarget_Callback(hObject, eventdata, handles)
% hObject    handle to SelectTarget (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Use uigetfile to pick a target file
[f , p] = uigetfile('*.csv' , 'Select a target asset CSV file');
if isnumeric(p) || isempty(f)
    return
end

handles.targetFile = fullfile(p , f);
set(handles.figure1 , 'pointer' , 'watch');
drawnow;

handles.assetLHS = f(1:2);

set(handles.figure1 , 'pointer' , 'arrow');
set(handles.TargetText , 'string' , f);

% Update handles structure
guidata(hObject, handles);

% --- Executes on button press in SelectSynthetic.
function SelectSynthetic_Callback(hObject, eventdata, handles)
% hObject    handle to SelectSynthetic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Use uigetfile to pick a synthetic file
[f , p] = uigetfile('*.csv' , 'Select a synthetic asset CSV file' , 'MultiSelect' , 'on');
if isnumeric(f) || isnumeric(p)
    return
end

set(handles.figure1 , 'pointer' , 'watch');

if ~iscell(f)
    tmp{1} = f;
    f = tmp;
end

textStr = [];
handles.assetRHS = {};
handles.SyntheticFile = {};
for i = 1:length(f)
    handles.SyntheticFile{i} = fullfile(p , f{i});
    handles.assetRHS{i} = f{i}(1:2);
    textStr = [textStr f{i} ' - '];
end
textStr = textStr(1:end-3);

set(handles.SyntheticText , 'string' , textStr);
set(handles.figure1 , 'pointer' , 'arrow');
guidata(hObject , handles);

% --- Executes on button press in EditParms.
function EditParms_Callback(hObject, eventdata, handles)
% hObject    handle to EditParms (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.params = editParDialog(handles.params);
guidata(hObject , handles);

% --- Executes on button press in RunStrategy.
function RunStrategy_Callback(hObject, eventdata, handles)
% hObject    handle to RunStrategy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles = i_LoadAllData(handles);

if isempty(handles.contractSpec)
    h = msgbox('Load in the contract spec file');
    uiwait(h);
    return
end

cSpecLHS = getContractSpecification(handles.assetLHS , handles.contractSpec);
for i = 1:length(handles.assetRHS)
    cSpecRHS(i) = getContractSpecification(handles.assetRHS{i} , handles.contractSpec);
end

% Call into the function signalSpreadTrade to generate the PnL
pnl = createSignalAndSpreadTrade(handles.dates , handles.closeLHS , handles.closeRHS , cSpecLHS , cSpecRHS , handles.params);
cla(handles.axes1);
plot(handles.dates , cumsum(pnl) , 'r');
axis('tight');
datetick('x' , 2 , 'keeplimits');

guidata(hObject , handles)

% --- Executes on button press in SetGrid.
function SetGrid_Callback(hObject, eventdata, handles)
% hObject    handle to SetGrid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


handles.paramGrid = editParGridDialog(handles.paramGrid);
guidata(hObject , handles);


% --- Executes on button press in RunGrid.
function RunGrid_Callback(hObject, eventdata, handles)
% hObject    handle to RunGrid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Manage the data
handles = i_LoadAllData(handles);

% Set up the grid
numDaysVec       = handles.paramGrid.numDays(1):handles.paramGrid.numDays(3):handles.paramGrid.numDays(2);
movAvgWindowVec  = handles.paramGrid.movAvgWindow(1):handles.paramGrid.movAvgWindow(3):handles.paramGrid.movAvgWindow(2);
openPositionVec  = handles.paramGrid.openPosition(1):handles.paramGrid.openPosition(3):handles.paramGrid.openPosition(2);
closePositionVec = handles.paramGrid.closePosition(1):handles.paramGrid.closePosition(3):handles.paramGrid.closePosition(2);
stopLossVec      = handles.paramGrid.stopLoss(1):handles.paramGrid.stopLoss(3):handles.paramGrid.stopLoss(2);
holdingPeriodVec = handles.paramGrid.holdingPeriod(1):handles.paramGrid.holdingPeriod(3):handles.paramGrid.holdingPeriod(2);

parComb = allcomb(movAvgWindowVec , openPositionVec , closePositionVec , stopLossVec , holdingPeriodVec);

% Run the grid
% Pre-allocate all the results sets for each of the individual runs
parResults = cell(length(numDaysVec) , 1);

set(handles.figure1 , 'pointer' , 'watch');

try
    % Open up a matlab pool
    disp('Opening up MATLAB pool')
    matlabpool local;
end

cSpecLHS = getContractSpecification(handles.assetLHS , handles.contractSpec);
for i = 1:length(handles.assetRHS)
    cSpecRHS(i) = getContractSpecification(handles.assetRHS{i} , handles.contractSpec); %#ok<AGROW>
end

% Send each batch of runs to a function that handles this parameter set
allPar = [];
parfor i = 1:length(numDaysVec)
    parResults{i} = runBacktestBatch(...
        numDaysVec(i) , ...
        parComb , ...
        handles.dates , ...
        handles.closeLHS , ...
        handles.closeRHS , ...
        cSpecLHS , cSpecRHS);
end

try
    matlabpool close
end
% Visualise the results
%
% Do a simple histogram plot of all the results
allPnl = [];
for i = 1:length(parResults)
    allPnl = [allPnl ; parResults{i}];
    allPar = [allPar ; repmat(numDaysVec(i) , size(parComb,1) , 1) parComb];    
end

cla(handles.axes1);
hist(allPnl , 100);

% Select the best strategy
allPnl(isnan(allPnl)) = -Inf;
[~,indx] = sort(allPnl , 'descend');

parVec = allPar(indx(1),:);

params.numDays        = parVec(1);
params.movAvgWindow   = parVec(2);
params.stdDevWindow   = parVec(2);
params.openPosition   = parVec(3);
params.closePosition  = parVec(4);
params.stopLoss       = parVec(5);
params.holdingPeriod  = parVec(6);

handles.params = params;
guidata(hObject , handles);

set(handles.figure1 , 'pointer' , 'arrow');

% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Load in the file
[f , p] = uigetfile('*.xml' , 'Select contract file');

if isnumeric(f) || isnumeric(p)
    return
end

% Get all the contract specs
handles.contractSpec = xml_read(fullfile(p,f));
guidata(hObject , handles);

%---------------------------------------------------------------------
function handles = i_LoadAllData(handles)
%---------------------------------------------------------------------
[dLHS , ohlcLHS] = getOhlcData(handles.targetFile);
closeLHS = ohlcLHS(:,4);
handles.dLHS = dLHS;
handles.closeLHS = closeLHS;

% Load in the synthetics
handles.argsRHS = {};
for i = 1:length(handles.SyntheticFile)
    fName = fullfile(handles.SyntheticFile{i});
    [dRHS , tmp] = getOhlcData(fName);
    closeRHS = tmp(:,4);
    handles.argsRHS = [handles.argsRHS dRHS closeRHS];
end

% Make sure that the data matches on date
[dates , data] = matchDataOnDates(handles.dLHS,handles.closeLHS,handles.argsRHS{:});

% First element is LHS, others are RHS
closeLHS = data{1};
closeRHS = [];
for i = 2:length(data)
    closeRHS = [closeRHS data{i}];
end

handles.dates = dates;
handles.closeLHS = closeLHS;
handles.closeRHS = closeRHS;

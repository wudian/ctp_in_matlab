function varargout = MatlabTrader(varargin)
% MATLABTRADER MATLAB code for MatlabTrader.fig
%      MATLABTRADER, by itself, creates a new MATLABTRADER or raises the existing
%      singleton*.
%
%      H = MATLABTRADER returns the handle to a new MATLABTRADER or the handle to
%      the existing singleton*.
%
%      MATLABTRADER('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MATLABTRADER.M with the given input arguments.
%
%      MATLABTRADER('Property','Value',...) creates a new MATLABTRADER or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before MatlabTrader_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to MatlabTrader_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help MatlabTrader

% Last Modified by GUIDE v2.5 26-Aug-2013 17:33:02

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @MatlabTrader_OpeningFcn, ...
                   'gui_OutputFcn',  @MatlabTrader_OutputFcn, ...
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


% --- Executes just before MatlabTrader is made visible.
function MatlabTrader_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to MatlabTrader (see VARARGIN)

% Choose default command line output for MatlabTrader
handles.output = hObject;

%% 初始化模块-MatlabTrader_OpeningFcn
global IDName;
load IDName;

global WBDF_OnOff;

WBDF_OnOff = 0;

movegui(gcf, 'north');

date = datestr(today,'yyyy/mm/dd');
ind = find(date=='/');
yyyy = date( 1:(ind(1)-1) );
mm = date( (ind(1)+1):(ind(2)-1) );
dd = date( (ind(2)+1):end );

set(handles.edit5,'String',yyyy);
set(handles.edit6,'String',mm);
set(handles.edit7,'String',dd);

set(handles.edit13,'String',yyyy);
set(handles.edit14,'String',mm);
set(handles.edit15,'String',dd);

% slider属性设置
set( handles.slider_TimeControl, 'Enable',  'off');

set( handles.pushbutton2, 'Enable',  'off');
set( handles.popupmenu2, 'Enable',  'off');
set( handles.popupmenu3, 'Enable',  'off');

cla(handles.axes1,'reset');
set(handles.axes1,'XTickLabel',[]);
set(handles.axes1,'YTickLabel',[]);
set(handles.axes1,'XTick',[]);
set(handles.axes1,'YTick',[]);

cla(handles.axes2,'reset');
set(handles.axes2,'XTickLabel',[]);
set(handles.axes2,'YTickLabel',[]);
set(handles.axes2,'XTick',[]);
set(handles.axes2,'YTick',[]);

cla(handles.axes3,'reset');
set(handles.axes3,'XTickLabel',[]);
set(handles.axes3,'YTickLabel',[]);
set(handles.axes3,'XTick',[]);
set(handles.axes3,'YTick',[]);

data = zeros(6,1);
set(handles.uitable1,'Data',data);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes MatlabTrader wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = MatlabTrader_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% 全局变量-pushbutton1_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

global WBDF_OnOff;

% 日线、周、月线
global stockmatD;
global stockmatW;
global stockmatM;

%% 从Yahoo获取数据
SecID = get(handles.edit1,'String');
HS = get(handles.popupmenu1,'Value');

if HS == 1
    SecID = [SecID,'.SS'];
else
    SecID = [SecID,'.SZ'];
end

if sum(strcmp(IDName(:,1),SecID)) == 0
    errordlg('请检查输入的代码是否有误或者沪深市是否选择错误');
    return;
end

SecName = IDName{strcmp(IDName(:,1),SecID) == 1, 2};
if HS == 1
    strtemp = ['沪市,',SecID,',',SecName];
else
    strtemp = ['深市,',SecID,',',SecName];
end
set(handles.text10,'String',strtemp);

Connect = yahoo;
if isconnection(Connect) == 0
    errordlg('请检查您的网络是否连接正常');
    return;
end
FromDate = [get(handles.edit2,'String'),'/',get(handles.edit3,'String'),'/',get(handles.edit4,'String')];
ToDate = [get(handles.edit5,'String'),'/',get(handles.edit6,'String'),'/',get(handles.edit7,'String')];
Fields = {'Open';'High';'Low';'Close';'Volume'};

% stock = fetch(Connect, SecID, Fields, FromDate, ToDate);
% stock = stock( end:(-1):1, : );

        stockmatD = fetch(Connect, SecID, Fields, FromDate, ToDate,'d');
        stockmatD = stockmatD( end:(-1):1, : );

        stockmatW = fetch(Connect, SecID, Fields, FromDate, ToDate,'w');
        stockmatW = stockmatW( end:(-1):1, : );        

        stockmatM = fetch(Connect, SecID, Fields, FromDate, ToDate,'m');
        stockmatM = stockmatM( end:(-1):1, : );        

% stockfts = fints(stock(:,1),stock(:,2:end),Fields,'D',SecID);

disp('==数据提取完成==');

%% 提取Open High Low Close Volume
% stockmat = fts2mat(stockfts,1);
temp = get(handles.popupmenu2,'Value');
switch temp
    case 1
        stockmat = stockmatD;
    case 2
        stockmat = stockmatW;
    case 3
        stockmat = stockmatM;
end


DatesNum = stockmat(:,1);
Open = stockmat(:,2);
High = stockmat(:,3);
Low = stockmat(:,4);
Close = stockmat(:,5);
Vol = stockmat(:,6);

xlim_min = 1;
xlim_max = size(stockmat, 1);

%% K线图形展示
cla(handles.axes1,'reset');
axes(handles.axes1);
MT_candle(High,Low,Close,Open,[],DatesNum);
hold on;

% MA1 = 5;
% MA2 = 10;
MA1 = str2double( get( handles.edit8,'String' ) );
MA2 = str2double( get( handles.edit9,'String' ) );

if ~isnumeric(MA1) || isempty(MA1) || isnan(MA1)
    warndlg('MA组合：MA1参数请输入数值', '警告！');
else
    if MA1 > length(Close)
        warndlg('MA组合：MA1参数请输入正确数值', '警告！');
    else
        axes(handles.axes1);
        h1 = plot( MA(Close,MA1), 'k');
        set(h1,'Tag', 'MA1');
    end
end

if ~isnumeric(MA2) || isempty(MA2) || isnan(MA2)
    warndlg('MA组合：MA2参数请输入数值', '警告！');
else
    if MA1 > length(Close)
        warndlg('MA组合：MA2参数请输入正确数值', '警告！');
    else
        axes(handles.axes1);
        h2 =plot( MA(Close,MA2), 'b');
        set(h2,'Tag', 'MA2');
    end
end

xlim(handles.axes1,[xlim_min-1, xlim_max+1]);

Hightemp = High;
Lowtemp = Low;

[Highest,hind] = max(Hightemp);
[Lowest,lind] = min(Lowtemp);

text(hind,Highest,['\leftarrow',num2str(Highest)]);
text(lind,Lowest,['\leftarrow',num2str(Lowest)]);

%% 成交量图形展示
cla(handles.axes2,'reset');
axes(handles.axes2);
set(gca,'XTickLabel',[]);
MT_VolumePlot( Open, High, Low, Close, Vol );
set(gca,'XTickLabel',[]);

xlim(handles.axes2,[xlim_min-1, xlim_max+1]);

%% 技术指标图形展示
cla(handles.axes3,'reset');
axes(handles.axes3);
set(gca,'XTickLabel',[]);

short = 12;
long = 26;
Mlen = 9;
if max([short long Mlen])<length(Close)
    MT_MACD(Close,short,long,Mlen);
    set(gca,'XTickLabel',[]);
    xlim(handles.axes3,[xlim_min-1, xlim_max+1]);
    
    str = ['MACD指标(','short=',num2str(short), ...
            ',long=',num2str(long),',MAlen=',num2str(Mlen),')'];
    set(handles.text16,'String',str);
end

% slider属性设置
set( handles.slider_TimeControl, 'Enable',  'off');

set( handles.pushbutton2, 'Enable',  'on');
set( handles.popupmenu2, 'Enable',  'on');
set( handles.popupmenu3, 'Enable',  'on');

WBDF_OnOff = 1;

% Update handles structure
guidata(hObject, handles);


function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2

%% 显示周期调整-popupmenu2_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

% 日线、周、月线
global stockmatD;
global stockmatW;
global stockmatM;

temp = get(handles.popupmenu2,'Value');
switch temp
    case 1
        stockmat = stockmatD;
    case 2
        stockmat = stockmatW;
    case 3
        stockmat = stockmatM;
end

DatesNum = stockmat(:,1);
Open = stockmat(:,2);
High = stockmat(:,3);
Low = stockmat(:,4);
Close = stockmat(:,5);
Vol = stockmat(:,6);

xlim_min = 1;
xlim_max = size(stockmat, 1);

% K线图形展示
cla(handles.axes1,'reset');
axes(handles.axes1);
MT_candle(High,Low,Close,Open,[],DatesNum);
hold on;

% MA1 = 5;
% MA2 = 10;
MA1 = str2double( get( handles.edit8,'String' ) );
MA2 = str2double( get( handles.edit9,'String' ) );

if ~isnumeric(MA1) || isempty(MA1) || isnan(MA1)
    warndlg('MA组合：MA1参数请输入数值', '警告！');
else
    if MA1 > length(Close)
        warndlg('MA组合：MA1参数请输入正确数值', '警告！');
    else
        axes(handles.axes1);
        h1 = plot( MA(Close,MA1), 'k');
        set(h1,'Tag', 'MA1');
    end
end

if ~isnumeric(MA2) || isempty(MA2) || isnan(MA2)
    warndlg('MA组合：MA2参数请输入数值', '警告！');
else
    if MA2 > length(Close)
        warndlg('MA组合：MA2参数请输入正确数值', '警告！');
    else
        axes(handles.axes1);
        h2 =plot( MA(Close,MA2), 'b');
        set(h2,'Tag', 'MA2');
    end
end

xlim(handles.axes1,[xlim_min-1, xlim_max+1]);

Hightemp = High;
Lowtemp = Low;

[Highest,hind] = max(Hightemp);
[Lowest,lind] = min(Lowtemp);

axes(handles.axes1);
text(hind,Highest,['\leftarrow',num2str(Highest)]);
text(lind,Lowest,['\leftarrow',num2str(Lowest)]);

% 成交量图形展示
cla(handles.axes2,'reset');
axes(handles.axes2);
set(gca,'XTickLabel',[]);
MT_VolumePlot( Open, High, Low, Close, Vol );
set(gca,'XTickLabel',[]);

xlim(handles.axes2,[xlim_min-1, xlim_max+1]);

% 技术指标图形展示
cla(handles.axes3,'reset');
axes(handles.axes3);
set(gca,'XTickLabel',[]);

short = 12;
long = 26;
Mlen = 9;
if max([short long Mlen])<length(Close)
    MT_MACD(Close,short,long,Mlen);
    set(gca,'XTickLabel',[]);
    xlim(handles.axes3,[xlim_min-1, xlim_max+1]);
    
    str = ['MACD指标(','short=',num2str(short), ...
        ',long=',num2str(long),',MAlen=',num2str(Mlen),')'];
    set(handles.text16,'String',str);
end

xlim(handles.axes3,[xlim_min-1, xlim_max+1]);

% slider属性设置
set( handles.slider_TimeControl, 'Enable',  'off');

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3

%% 计算指标展示-popupmenu3_Callback

global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

% 日线、周、月线
global stockmatD;
global stockmatW;
global stockmatM;

cla(handles.axes3,'reset');
axes(handles.axes3);
set(gca,'XTickLabel',[]);

temp = get(handles.popupmenu3,'Value');
switch temp
    % MACD
    case 1
        short = 12;
        long = 26;
        Mlen = 9;
        if max([short long Mlen])<length(Close)
            MT_MACD(Close,short,long,Mlen);
            
            str = ['MACD指标(','short=',num2str(short), ...
                ',long=',num2str(long),',MAlen=',num2str(Mlen),')'];
            set(handles.text16,'String',str);
        end
        
    %  Boll
    case 2
        wsize = 20;
        nstd = 2;
        wts = 0;
        if wsize<length(Close)
            [mid, uppr, lowr] = bollinger(Close, wsize, wts, nstd);
            
            MT_candle(High,Low,Close,Open,[],DatesNum);
            hold on;
           
            plot([uppr,mid,lowr]);
            
            str = ['Bollinger band指标(','wsize=',num2str(wsize), ...
                ',nstd=',num2str(nstd), ')'];
            set(handles.text16,'String',str);            
        end
        
    % RSI    
    case 3
        nperiods = 14;

        if nperiods<length(Close)
            rsi = rsindex(Close, nperiods);
            
            plot(rsi);
            str = ['RSI指标(','nperiods=',num2str(nperiods), ')'];
            set(handles.text16,'String',str);            
        end        
        
    % W&R   
    case 4
        nperiods = 14;
        if nperiods<length(Close)
            wpctr = willpctr(High, Low, Close, nperiods);
            
            plot(wpctr);
            str = ['Williams %R指标(','nperiods=',num2str(nperiods), ')'];
            set(handles.text16,'String',str);            
        end        
        
    % OBV  
    case 5    

        if 1
            obv = onbalvol(Close, Vol);
            
            plot(obv);
            
            str = ['OBV指标'];
            set(handles.text16,'String',str);            
        end        
        
    % DMI   
    case 6
        N = 14;
        M = 6;
        if max(N,M)<length(Close)
             [PDI, MDI, DX, ADX, ADXR] = DMI_General(Open,High,Low,Close,N,M);
            
            plot([PDI, MDI,ADX,ADXR]);
            legend('PDI', 'MDI','ADX','ADXR');
            str = ['DMI指标(','N=',num2str(N), ...
                ',M=',num2str(M), ')'];
            set(handles.text16,'String',str);            
        end
        
     %   Chaikin oscillator
    case 7

        if 1
            chosc = chaikosc(High, Low, Close, Vol);
            
            plot([chosc]);

            str = ['Chaikin oscillator指标'];
            set(handles.text16,'String',str);            
        end        
     
     %   Chaikin volatility
    case 8        

        if 1
             chvol = chaikvolat(High, Low);
            
            plot([chvol]);

            str = ['Chaikin volatility指标'];
            set(handles.text16,'String',str);            
        end        
     %   Price and Volume Trend (PVT)
    case 9

        if 1
             pvt = pvtrend(Close, Vol);
            
            plot([pvt]);

            str = ['Price and Volume Trend (PVT)指标'];
            set(handles.text16,'String',str);            
        end     

end

set(gca,'XTickLabel',[]);
set( handles.axes3, 'XLim', get(handles.axes1,'XLim') );

% Update handles structure
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider_TimeControl_Callback(hObject, eventdata, handles)
% hObject    handle to slider_TimeControl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

%% slider_TimeControl_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

DemoFromDate = [get(handles.edit10,'String'),'/',get(handles.edit11,'String'),'/',get(handles.edit12,'String')];
DemoToDate = [get(handles.edit13,'String'),'/',get(handles.edit14,'String'),'/',get(handles.edit15,'String')];

DemoFromDateNum = datenum( DemoFromDate, 'yyyy/mm/dd' );
DemoToDateNum = datenum( DemoToDate, 'yyyy/mm/dd' );

xlim_min = 1;
xlim_max = size(stockmat, 1);

indtemp = find( DatesNum >= DemoFromDateNum );
xlimL_Demo = indtemp(1);
indtemp = find( DatesNum <= DemoToDateNum );
xlimR_Demo = indtemp(end);

SliderValue = get( handles.slider_TimeControl, 'Value' );
xlimR = floor( SliderValue );
xlimL = xlimR - ( xlimR_Demo-xlimL_Demo );
if xlimR >xlim_max
    xlimR = xlim_max;
end
if xlimL < xlim_min
    xlimL = xlim_min;
end

% 调整xlim
xlim(handles.axes1,[xlimL, xlimR]);
xlim(handles.axes2,[xlimL, xlimR]);
xlim(handles.axes3,[xlimL, xlimR]);

% xtick重新绘制
newTick = linspace(xlimL,xlimR,4)';
newTick = floor(newTick);
newTickChar = datestr(DatesNum(newTick));
newTickLabel = cell(4,1);
for i = 1:4
    newTickLabel{i,1} = newTickChar(i,:);
end

set(handles.axes1,'XTick',newTick);
set(handles.axes1,'XTickLabel',newTickLabel);

% 高低点重新绘制
Htemp = findobj(handles.axes1,'Type','Text');
if ~isempty(Htemp)
    delete(Htemp);
end

Hightemp = High(xlimL:xlimR);
Lowtemp = Low(xlimL:xlimR);

[Highest,hind] = max(Hightemp);
[Lowest,lind] = min(Lowtemp);
axes(handles.axes1);
hold on;
text(hind+xlimL-1,Highest,['\leftarrow',num2str(Highest)]);
text(lind+xlimL-1,Lowest,['\leftarrow',num2str(Lowest)]);


% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function slider_TimeControl_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_TimeControl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double

%% 均线长度MA1-edit8_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

MA1 = str2double( get(handles.edit8,'String') );
if ~isnumeric(MA1) || isempty(MA1) || isnan(MA1)
    warndlg('请输入数值', '警告！');
    return;
end
if MA1 > length(Close)
    warndlg('请输入正确数值', '警告！');
    return;    
end

Htemp = findobj(handles.axes1,'Tag','MA1');
if ~isempty(Htemp)
    delete(Htemp);
end

axes(handles.axes1);
hold on;
h1 = plot( MA(Close,MA1), 'k');
set(h1,'Tag', 'MA1');

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double
%% 均线长度MA2-edit9_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

MA2 = str2double( get(handles.edit9,'String') );
if ~isnumeric(MA2) || isempty(MA2) || isnan(MA2)
    warndlg('请输入数值', '警告！');
    return;
end
if MA2 > length(Close)
    warndlg('请输入正确数值', '警告！');
    return;    
end

Htemp = findobj(handles.axes1,'Tag','MA2');
if ~isempty(Htemp)
    delete(Htemp);
end

axes(handles.axes1);
hold on;
h1 = plot( MA(Close,MA2), 'b');
set(h1,'Tag', 'MA2');

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Update handles structure
guidata(hObject, handles);

% --- Executes during object deletion, before destroying properties.
function figure1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% Update handles structure
guidata(hObject, handles);


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% 展示范围调整-pushbutton2_Callback
global IDName;
global stockmat;
global DatesNum;
global Open;
global High;
global Low;
global Close;
global Vol;

FromDate = [get(handles.edit2,'String'),'/',get(handles.edit3,'String'),'/',get(handles.edit4,'String')];
ToDate = [get(handles.edit5,'String'),'/',get(handles.edit6,'String'),'/',get(handles.edit7,'String')];

FromDateNum = datenum( FromDate, 'yyyy/mm/dd' );
ToDateNum = datenum( ToDate, 'yyyy/mm/dd' );

DemoFromDate = [get(handles.edit10,'String'),'/',get(handles.edit11,'String'),'/',get(handles.edit12,'String')];
DemoToDate = [get(handles.edit13,'String'),'/',get(handles.edit14,'String'),'/',get(handles.edit15,'String')];

DemoFromDateNum = datenum( DemoFromDate, 'yyyy/mm/dd' );
DemoToDateNum = datenum( DemoToDate, 'yyyy/mm/dd' );

if DemoFromDateNum<FromDateNum || DemoFromDateNum>ToDateNum
    errordlg('请检查输入的展示起始日期是否输入错误');
    return;
end
if DemoToDateNum<FromDateNum || DemoToDateNum>ToDateNum
    errordlg('请检查输入的展示终止日期是否输入错误');
    return;
end
if DemoFromDateNum>DemoToDateNum
    errordlg('请检查输入的展示起始日期和终止日期是否输入错误');
    return;
end

xlim_min = 1;
xlim_max = size(stockmat, 1);

indtemp = find( DatesNum >= DemoFromDateNum );
xlimL = indtemp(1);
indtemp = find( DatesNum <= DemoToDateNum );
xlimR = indtemp(end);

% 调整xlim
xlim(handles.axes1,[xlimL, xlimR]);
xlim(handles.axes2,[xlimL, xlimR]);
xlim(handles.axes3,[xlimL, xlimR]);

% xtick重新绘制
newTick = linspace(xlimL,xlimR,4)';
newTick = floor(newTick);
newTickChar = datestr(DatesNum(newTick));
newTickLabel = cell(4,1);
for i = 1:4
    newTickLabel{i,1} = newTickChar(i,:);
end

set(handles.axes1,'XTick',newTick);
set(handles.axes1,'XTickLabel',newTickLabel);

% 高低点重新绘制
Htemp = findobj(handles.axes1,'Type','Text');
if ~isempty(Htemp)
    delete(Htemp);
end

Hightemp = High(xlimL:xlimR);
Lowtemp = Low(xlimL:xlimR);

[Highest,hind] = max(Hightemp);
[Lowest,lind] = min(Lowtemp);
axes(handles.axes1);
hold on;
text(hind+xlimL-1,Highest,['\leftarrow',num2str(Highest)]);
text(lind+xlimL-1,Lowest,['\leftarrow',num2str(Lowest)]);

% 更新slider相关属性
if xlim_min+xlimR-xlimL<xlim_max
    set( handles.slider_TimeControl, 'Enable',  'on');
    set( handles.slider_TimeControl, 'Max',  xlim_max);
    set( handles.slider_TimeControl, 'Min',  xlim_min+xlimR-xlimL);
    
    set( handles.slider_TimeControl, 'Value',  xlimR);
    
    sliderstepx = 1/( xlim_max-(xlim_min+xlimR-xlimL) );
    sliderstepy = 3/( xlim_max-(xlim_min+xlimR-xlimL) );
    set( handles.slider_TimeControl, 'SliderStep',  [sliderstepx,sliderstepy]);
else
    set( handles.slider_TimeControl, 'Enable',  'off');
end
% Update handles structure
guidata(hObject, handles);


function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit12 as text
%        str2double(get(hObject,'String')) returns contents of edit12 as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit13_Callback(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit13 as text
%        str2double(get(hObject,'String')) returns contents of edit13 as a double


% --- Executes during object creation, after setting all properties.
function edit13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit14_Callback(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit14 as text
%        str2double(get(hObject,'String')) returns contents of edit14 as a double


% --- Executes during object creation, after setting all properties.
function edit14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit15_Callback(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit15 as text
%        str2double(get(hObject,'String')) returns contents of edit15 as a double


% --- Executes during object creation, after setting all properties.
function edit15_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on mouse motion over figure - except title and menu.
function figure1_WindowButtonMotionFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% 鼠标移动函数-figure1_WindowButtonMotionFcn
test = 0;
if 1 == test
    global IDName;
    global stockmat;
    global DatesNum;
    global Open;
    global High;
    global Low;
    global Close;
    global Vol;
    
    % 日线、周、月线
    global stockmatD;
    global stockmatW;
    global stockmatM;
    
    cp = get(handles.axes1, 'CurrentPoint');
    x = cp(1,1);
    y = cp(1,2);
    
%     Htemp = findobj(handles.axes1,'Tag','LineX');
%     if ~isempty(Htemp)
%         delete(Htemp);
%     end
%     Htemp = findobj(handles.axes1,'Tag','LineY');
%     if ~isempty(Htemp)
%         delete(Htemp);
%     end
%     Htemp = findobj(handles.axes2,'Tag','LineY');
%     if ~isempty(Htemp)
%         delete(Htemp);
%     end
%     Htemp = findobj(handles.axes3,'Tag','LineY');
%     if ~isempty(Htemp)
%         delete(Htemp);
%     end  
    
    axes(handles.axes1);
    xlimvalue = xlim;
    ylimvalue = ylim;
    
    axes(handles.axes2);
    xlim2value = xlim;
    ylim2value = ylim;
    
    axes(handles.axes3);
    xlim3value = xlim;
    ylim3value = ylim;    
    
    if x>xlimvalue(1) && x<xlimvalue(2) ...
            && y>ylimvalue(1) && y<ylimvalue(2)
        axes(handles.axes1);
        hold on;
        line( [x,x],[ylimvalue(1),ylimvalue(2)],'Color','r','Tag','LineY' );
        line( [xlimvalue(1),xlimvalue(2)],[y,y],'Color','r','Tag','LineX' );
        
        axes(handles.axes2);
        hold on;
        line( [x,x],[ylim2value(1),ylim2value(2)],'Color','r','Tag','LineY' );
        
        axes(handles.axes3);
        hold on;
        line( [x,x],[ylim3value(1),ylim3value(2)],'Color','r','Tag','LineY' );    
        
    end
    
end
    
% Update handles structure
guidata(hObject, handles);


% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function figure1_WindowButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% 鼠标左键按下函数-figure1_WindowButtonDownFcn

global WBDF_OnOff;

test = 1;
if 1 == test && 1 == WBDF_OnOff
    global IDName;
    global stockmat;
    global DatesNum;
    global Open;
    global High;
    global Low;
    global Close;
    global Vol;
    
    % 日线、周、月线
    global stockmatD;
    global stockmatW;
    global stockmatM;
    
    cp = get(handles.axes1, 'CurrentPoint');
    x = cp(1,1);
    y = cp(1,2);
    
    Htemp = findobj(handles.axes1,'Tag','LineX');
    if ~isempty(Htemp)
        delete(Htemp);
    end
    Htemp = findobj(handles.axes1,'Tag','LineY');
    if ~isempty(Htemp)
        delete(Htemp);
    end
    Htemp = findobj(handles.axes2,'Tag','LineY');
    if ~isempty(Htemp)
        delete(Htemp);
    end
    Htemp = findobj(handles.axes3,'Tag','LineY');
    if ~isempty(Htemp)
        delete(Htemp);
    end  
    
    axes(handles.axes1);
    xlimvalue = xlim;
    ylimvalue = ylim;
    
    axes(handles.axes2);
    xlim2value = xlim;
    ylim2value = ylim;
    
    axes(handles.axes3);
    xlim3value = xlim;
    ylim3value = ylim;    
    
    if x>xlimvalue(1) && x<xlimvalue(2) ...
            && y>ylimvalue(1) && y<ylimvalue(2)
        axes(handles.axes1);
        hold on;
        line( [x,x],[ylimvalue(1),ylimvalue(2)],'Color','r','Tag','LineY' );
        line( [xlimvalue(1),xlimvalue(2)],[y,y],'Color','r','Tag','LineX' );
        
        axes(handles.axes2);
        hold on;
        line( [x,x],[ylim2value(1),ylim2value(2)],'Color','r','Tag','LineY' );
        
        axes(handles.axes3);
        hold on;
        line( [x,x],[ylim3value(1),ylim3value(2)],'Color','r','Tag','LineY' );    
        
        
        % 展示开高低收量
        x = round(x);
        if x>length(DatesNum)
            x = length(DatesNum);
        end
        if x<1
            x = 1;
        end
        Datetemp = DatesNum(x);
        Datetemp = datestr( Datetemp,'yyyymmdd' );
        Datetemp = str2double(Datetemp);
        Opentemp = Open(x);
        Hightemp = High(x);
        Lowtemp = Low(x);
        Closetemp = Close(x);
        Voltemp = Vol(x);
        
        data = [Datetemp; Opentemp;Hightemp;Lowtemp;Closetemp;Voltemp];
        set(handles.uitable1,'Data',data);
    end

    
end
% Update handles structure
guidata(hObject, handles);


% --------------------------------------------------------------------
function savepic1_Callback(hObject, eventdata, handles)
% hObject    handle to savepic1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% axes1右键-savepic1_Callback
axes(handles.axes1);
if isempty(handles.axes1)
    return;
end
newfig = figure;
set(newfig,'Visible','off');
newaxes = copyobj(handles.axes1,newfig);
set(newaxes,'Units','default','Position','default');

[filename,pathname,filterindex] = uiputfile({'*.jpg';'*.*'},'save as');

if filterindex
    filename=strcat(pathname,filename);
    pic = getframe(newfig);
    pic = frame2im(pic);
    imwrite(pic, filename);
end

guidata(hObject,handles);

% --------------------------------------------------------------------
function pic1_Callback(hObject, eventdata, handles)
% hObject    handle to pic1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function pic2_Callback(hObject, eventdata, handles)
% hObject    handle to pic2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function savepic2_Callback(hObject, eventdata, handles)
% hObject    handle to savepic2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%% axes2右键-savepic2_Callback
axes(handles.axes2);
if isempty(handles.axes2)
    return;
end
newfig = figure;
set(newfig,'Visible','off');
newaxes = copyobj(handles.axes2,newfig);
set(newaxes,'Units','default','Position','default');

[filename,pathname,filterindex] = uiputfile({'*.jpg';'*.*'},'save as');

if filterindex
    filename=strcat(pathname,filename);
    pic = getframe(newfig);
    pic = frame2im(pic);
    imwrite(pic, filename);
end

guidata(hObject,handles);


% --------------------------------------------------------------------
function savepic3_Callback(hObject, eventdata, handles)
% hObject    handle to savepic3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%% axes3右键-savepic2_Callback
axes(handles.axes3);
if isempty(handles.axes3)
    return;
end
newfig = figure;
set(newfig,'Visible','off');
newaxes = copyobj(handles.axes3,newfig);
set(newaxes,'Units','default','Position','default');

[filename,pathname,filterindex] = uiputfile({'*.jpg';'*.*'},'save as');

if filterindex
    filename=strcat(pathname,filename);
    pic = getframe(newfig);
    pic = frame2im(pic);
    imwrite(pic, filename);
end

guidata(hObject,handles);

% --------------------------------------------------------------------
function pic3_Callback(hObject, eventdata, handles)
% hObject    handle to pic3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

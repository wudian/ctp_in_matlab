function par = editParDialog(par)

h = i_GetHandle;
if ~isempty(h)
    for i = 1:length(h)
        delete(h(i));
    end
end
h = i_Create(par);
waitfor(h , 'visible' , 'off');
d = i_GetData;
if d.Ok
    par = d.par;
else
    par = d.parCopy;
end
delete(h);

function h = i_Create(par)

figW = 300;
figH = 250;
sSize = get(0 , 'screenSize');
scrW = sSize(3);
scrH = sSize(4);
Handles.Figure = figure(...
    'position' , [scrW/2-figW/2 , scrH/2-figH/2 , figW , figH] , ...
    'menubar' , 'none' , ...
    'numbertitle' , 'off' , ...
    'tag' , mfilename , ...
    'closerequestfcn' , @i_Cancel);

Handles.Table = uitable(...
    'position' , [10 50 figW-20 figH-60] , ...
    'columneditable' , [false true]);

Handles.Ok = uicontrol(...
    'parent' , Handles.Figure , ...
    'position' , [figW-160 10 70 30] , ...
    'string' , 'Ok' , ...
    'callback' , @i_Ok);

Handles.Cancel = uicontrol(...
    'parent' , Handles.Figure , ...
    'position' , [figW-80 10 70 30] , ...
    'string' , 'Cancel' , ...
    'callback' , @i_Cancel);

% Turn the data into a cell array
fNames = fieldnames(par);
cell = fNames;
cell{end,2} = [];
for i = 1:length(fNames)
    cell{i,2} = par.(fNames{i});
end

set(Handles.Table , 'data' , cell , 'ColumnName' , {'Parameter' , 'Value'});

d.par = par;
d.parCopy = par;
d.Handles = Handles;
d.Ok = 0;
i_SetData(d);
h = d.Handles.Figure;

%--------------------------------------------------------------------------
function h = i_GetHandle
%--------------------------------------------------------------------------
h = findobj(0 , 'tag' , mfilename);


%--------------------------------------------------------------------------
function d = i_GetData
%--------------------------------------------------------------------------
d = get(i_GetHandle , 'userdata');

%--------------------------------------------------------------------------
function i_SetData(d)
%--------------------------------------------------------------------------
set(i_GetHandle , 'userdata' , d);

%--------------------------------------------------------------------------
function i_Ok(varargin)
%--------------------------------------------------------------------------
d = i_GetData;
d.Ok = 1;

% Get the data from the table
data = get(d.Handles.Table , 'data');
fn = fieldnames(d.par);
for i = 1:length(fn)
    d.par.(fn{i}) = data{i,2};
end

i_SetData(d);
i_Cancel;

%--------------------------------------------------------------------------
function i_Cancel(varargin)
%--------------------------------------------------------------------------
set(i_GetHandle , 'visible' , 'off');

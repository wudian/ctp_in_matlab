function startup

% Set up paths for data
whichDir = fileparts(which(mfilename));

% Which directories do we have under here?
nextDir = 'Data';

% Add this top level data directory
addpath([whichDir filesep nextDir]);

% Find all the directories lower down
s = dir([whichDir filesep nextDir]);
for i = 3:length(s)
    if s(i).isdir
        addpath([whichDir filesep nextDir filesep s(i).name]);
    end
end

otherDirs = {...
    'Charts' , 'gaFiles' , 'Models' , 'Demo_5' , 'Demo_7'};
for i = 1:length(otherDirs)
    addpath([whichDir filesep otherDirs{i}]);
end

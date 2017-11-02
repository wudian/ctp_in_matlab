function [dateOut , varargout] = matchDataOnDates(varargin)
%function [dates , varargout] = matchDataOnDates(varargin)
%
% Matches up data in pairs.

% collate all the dates
dates = varargin(1:2:end);
data = varargin(2:2:end);

% Now collect the total intersection of the dates
dateOut = intersect(dates{1} , dates{2});
for i = 3:length(dates)
    dateOut = intersect(dateOut , dates{i});
end

% Now go through each original time, and find out where this date vector is
for i = 1:length(data)
    
    [~,whichRows] = intersect(dates{i} , dateOut);
    data{i} = data{i}(whichRows,:);
    
end

if nargout == 2
    varargout{1} = data;
else
    varargout = data;
end


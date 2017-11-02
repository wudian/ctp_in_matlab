function [dates,ohlc] = getOhlcData(fName)
%function [dates,ohlc] = getOhlcData(fName)
%
% Reads in the OHLC format text file

% Open the file in read-only mode
fid = fopen(fName , 'r');

% Read in the data using textscan

% Create a format string
formatStr = '%s%f%f%f%f%[^\n\r]';
C = textscan(fid , formatStr , 'delimiter' , ',');

dates = C{1};
ohlc = [C{2} C{3} C{4} C{5}];

% Close the file
fclose(fid);

% Convert the dates to matlab serial date numbers
dates = char(dates);
dates = dates(:,1:8);
dates = datenum(dates , 'yyyymmdd');

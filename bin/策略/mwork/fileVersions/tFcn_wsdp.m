function tFcn_wsdp(obj,eventdata,UserData)
%IMPORTFILE Import numeric data from a text file as column vectors.

%% Initialize variables.
UD = obj.UserData;
filename = UD.filename;

delimiter = ',';
startRow = 2;
endRow = inf;

%% Read columns of data as strings:
% For more information, see the TEXTSCAN documentation.
formatSpec = '%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%[^\n\r]';

%% Open the text file.
fileID = fopen(filename,'r');

%% Read columns of data according to format string.
% This call is based on the structure of the file used to generate this
% code. If an error occurs for a different file, try regenerating the code
% from the Import Tool.
dataArray = textscan(fileID, formatSpec, endRow(1)-startRow(1)+1, 'Delimiter', delimiter, 'HeaderLines', startRow(1)-1, 'ReturnOnError', false);
for block=2:length(startRow)
    frewind(fileID);
    dataArrayBlock = textscan(fileID, formatSpec, endRow(block)-startRow(block)+1, 'Delimiter', delimiter, 'HeaderLines', startRow(block)-1, 'ReturnOnError', false);
    for col=1:length(dataArray)
        dataArray{col} = [dataArray{col};dataArrayBlock{col}];
    end
end

%% Close the text file.
fclose(fileID);

%% Convert the contents of columns containing numeric strings to numbers.
% Replace non-numeric strings with NaN.
raw = repmat({''},length(dataArray{1}),length(dataArray)-1);
for col=1:length(dataArray)-1
    raw(1:length(dataArray{col}),col) = dataArray{col};
end
numericData = NaN(size(dataArray{1},1),size(dataArray,2));

for col=[2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]
    % Converts strings in the input cell array to numbers. Replaced non-numeric
    % strings with NaN.
    rawData = dataArray{col};
    for row=1:size(rawData, 1);
        % Create a regular expression to detect and remove non-numeric prefixes and
        % suffixes.
        regexstr = '(?<prefix>.*?)(?<numbers>([-]*(\d+[\,]*)+[\.]{0,1}\d*[eEdD]{0,1}[-+]*\d*[i]{0,1})|([-]*(\d+[\,]*)*[\.]{1,1}\d+[eEdD]{0,1}[-+]*\d*[i]{0,1}))(?<suffix>.*)';
        try
            result = regexp(rawData{row}, regexstr, 'names');
            numbers = result.numbers;
            
            % Detected commas in non-thousand locations.
            invalidThousandsSeparator = false;
            if any(numbers==',');
                thousandsRegExp = '^\d+?(\,\d{3})*\.{0,1}\d*$';
                if isempty(regexp(thousandsRegExp, ',', 'once'));
                    numbers = NaN;
                    invalidThousandsSeparator = true;
                end
            end
            % Convert numeric strings to numbers.
            if ~invalidThousandsSeparator;
                numbers = textscan(strrep(numbers, ',', ''), '%f');
                numericData(row, col) = numbers{1};
                raw{row, col} = numbers{1};
            end
        catch me
        end
    end
end

%% Split data into numeric and cell columns.
rawNumericColumns = raw(:, [2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]);
rawCellColumns = raw(:, 1);


%% Replace non-numeric cells with NaN
R = cellfun(@(x) ~isnumeric(x) && ~islogical(x),rawNumericColumns); % Find non-numeric cells
rawNumericColumns(R) = {NaN}; % Replace non-numeric cells

%% Allocate imported array to column variable names
Time = rawCellColumns(:, 1);
Code = cell2mat(rawNumericColumns(:, 1));
NewPrice = cell2mat(rawNumericColumns(:, 2));
BP1 = cell2mat(rawNumericColumns(:, 3));
BP2 = cell2mat(rawNumericColumns(:, 4));
BP3 = cell2mat(rawNumericColumns(:, 5));
BP4 = cell2mat(rawNumericColumns(:, 6));
BP5 = cell2mat(rawNumericColumns(:, 7));
BV1 = cell2mat(rawNumericColumns(:, 8));
BV2 = cell2mat(rawNumericColumns(:, 9));
BV3 = cell2mat(rawNumericColumns(:, 10));
BV4 = cell2mat(rawNumericColumns(:, 11));
BV5 = cell2mat(rawNumericColumns(:, 12));
SP1 = cell2mat(rawNumericColumns(:, 13));
SP2 = cell2mat(rawNumericColumns(:, 14));
SP3 = cell2mat(rawNumericColumns(:, 15));
SP4 = cell2mat(rawNumericColumns(:, 16));
SP5 = cell2mat(rawNumericColumns(:, 17));
SV1 = cell2mat(rawNumericColumns(:, 18));
SV2 = cell2mat(rawNumericColumns(:, 19));
SV3 = cell2mat(rawNumericColumns(:, 20));
SV4 = cell2mat(rawNumericColumns(:, 21));
SV5 = cell2mat(rawNumericColumns(:, 22));


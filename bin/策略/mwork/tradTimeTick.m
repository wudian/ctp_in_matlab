function  itick= tradTimeTick( SI, timeStr )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
try
    try
        t = datevec(timeStr,'yyyy/mm/dd HH:MM:SS');
    catch
        t = datevec(timeStr,'yyyy-mm-dd HH:MM:SS');
    end
catch
    t = [];
    itick = 0;
end
% if get Date Vector correctly, return valid ITICK
if ~isempty(t)
    switch t(4)
        case {10,11}
            itick = ceil(t(6)/SI) + t(5)*(60/SI) + ((t(4)-9)*60-30)*(60/SI) + 1;
        case {13,14,15}
            itick = ceil(t(6)/SI) + t(5)*(60/SI) + (t(4)-11)*60*(60/SI) + 1;
        case 9        
                if t(5)>=30
                    itick = ceil(t(6)/SI) + (t(5)-30)*(60/SI) +1;
                else
                    itick = 1;
                end
    end
end

end


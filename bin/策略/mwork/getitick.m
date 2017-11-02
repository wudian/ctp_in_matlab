function it = getitick( SI, trytimes, datecell )
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
it = 1;
for i=1:trytimes
    try
        itick= tradTimeTick( SI, cell2mat(datecell(i)) );
    catch
        continue
    end
    if itick>it
        it = itick;
    end
end


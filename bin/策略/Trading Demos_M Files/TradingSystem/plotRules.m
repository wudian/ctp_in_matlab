function state = plotRules(options, state, flag)

if isstruct(state)
    imagesc(state.Population);
    set(gca,'XTick',1:size(state.Population,2))
else
    imagesc(state);
    set(gca,'XTick',1:size(state,2))
end

xlabel('Bit Position'); ylabel('Individual in Population')
colormap([1 0 0; 0 1 0]); 
axis tight
%%
% Copyright 2010-2012, The MathWorks, Inc.
% All rights reserved.
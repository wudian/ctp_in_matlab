function state = plotRules(options, state, flag)
imagesc(state.Population);
xlabel('Bit Position'); ylabel('Individual in Population')
colormap([1 0 0; 0 1 0]); set(gca,'XTick',1:size(state.Population,2))
axis tight
%%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.
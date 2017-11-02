function isoplot(xx,yy,zz,u,redvals,yelvals,bluevals)


%
% Copyright 2010, The MathWorks, Inc.
% All rights reserved.

% red
red=[0.5 0 0];
for i=1:length(redvals)
    pH = patch(isosurface(xx,yy,zz,u,redvals(i)));
    set(pH,'facecolor',red,'edgecolor','none','facealpha',0.3);
end

% yellow
yellow=[0.8 0.8 0];
for i=1:length(yelvals)
    pH= patch(isosurface(xx,yy,zz,u,yelvals(i)));
    set(pH,'facecolor',yellow,'edgecolor','none','facealpha',0.1)
end

% blue
blue = [0 0 0.5];
for i=1:length(bluevals)
    pH= patch(isosurface(xx,yy,zz,u,bluevals(i)));
    set(pH,'facecolor',blue,'edgecolor','none','facealpha',0.3);
end

% lighting
light('pos',[-100,50,100]); 
light('pos',[50,-100,100]); 
light('pos',[-100,-100,1]); 
light('pos',[1,0,1]);
lighting phong
%set(gca,'view',[-109,9],'projection','orth')
% cameramenu on


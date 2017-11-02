function out = movingStdDev(in , winLength)

out = zeros(size(in));
for i = winLength:length(in)
    out(i) = std(in(i-winLength+1:i) , 1);
end

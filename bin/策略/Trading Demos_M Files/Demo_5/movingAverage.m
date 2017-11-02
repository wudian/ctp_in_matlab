function out = movingAverage(in , winLength)

out = zeros(size(in));
for i = winLength:length(in)
    out(i) = mean(in(i-winLength+1:i));
end

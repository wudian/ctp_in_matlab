function y = cal_k(x)

%% input: a matrix  x  for several records
%% output: [Open High Low End] for x

y = zeros(1,4); 
len = size(x,1);     %% row of x
y(1) = x(1,1);       %% new open
y(2) = max(x(:,2));  %% new high
y(3) = min(x(:,3));  %% new low
y(4) = x(len,4);     %% new end


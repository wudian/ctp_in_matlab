function SigMat = sigCand(Kdata)

Pattn = 1:90;
nPattern = numel(Pattn);
[ns,nd] = size(Kdata(:,:,1));
SigMat = false([ns,nd,nPattern]);

for i=1:ns
    if mod(i,100)==0
        disp(i)
    end
    Open = fliplr(Kdata(i,:,1));
    High = fliplr(Kdata(i,:,2));
    Low  = fliplr(Kdata(i,:,3));
    Close= fliplr(Kdata(i,:,4));
    Open = Open';
    High = High';
    Low = Low';
    Close = Close';
    if min(Low)==0
        continue;
    end
    %% Signals of Raising 10 percent in one day.
    ir = (Close(2:end)-Close(1:end-1))./Close(1:end-1);
    idx = [false;ir>0.095]';
    %% 
    [bull, bear, neutral] = candlesticks(Open,High,Low,Close);
    SC = [bull; bear; neutral];
    for j = 1:nPattern
        if ~isempty(SC{Pattn(j)})
            M = false([1,nd]);
            M(SC{Pattn(j)}) = true;
            M(idx) = false; % Remove Signals with 10 percent raising
            SigMat(i,:,j) = fliplr(M);
        end
    end     
end
function flg = fetchSave( Connect, Security, Fields, FromDate, ToDate )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
        try
            %FETCH: Request data from Yahoo! Finance
            stock = fetch(Connect, Security, Fields, FromDate, ToDate);
%           stock = fetch(Connect, Security, Fields);
        catch
            warning('Failed to fetch %s.',Security);
            flg = 0;
            return;
        end    
        stock = stock( end:(-1):1, : );    
         stock = stock(stock(:,end)>0,:);  %% New added -- May 27,2014
        stockfts = fints(stock(:,1),stock(:,2:end),Fields,'D',Security);
        stockfts = stockfts(fts2mat(stockfts.Volume)>0); % Remove no trading volume data.
                
        %´æ´¢MatÎÄ¼ş
        ss=[Security(8:9),Security(1:6)];
        fpathname=[pwd, '\fdata\', ss, '.mat'];
        ss2=[ss,'=stockfts;'];
        eval(ss2); % Save fts data with a specified variable name.
        save(fpathname, ss); % Save to Mat file
        
        flg =1;
end


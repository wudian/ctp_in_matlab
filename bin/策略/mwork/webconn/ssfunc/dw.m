
%% Daily Work
% N : Switch flg
%%
% clear all;
% %% Data Fetch and Formatting
fetchHistData2;
formatFts2mat(900);
% %% Daily Go Through with All SS Functions
load corpList.mat
load dk1.mat
nD0 = 9; 
[SigMat0,J]=ssSd(dk1,dk1_date,-1,nD0, 1,1);
if J>0      
    corpList_S(SigMat0)
end
% 
% %% Candle Stick Patern

ss_scrpt_05;

% K = dk1(:,1:20,:);
% Kdate = dk1_date(:,1,:);
% Pattn = [1 2 3 6 28 39];
% PattnName = {'01.Abandoned Baby',...
%                 '02.Concealing Baby Swallow',...
%                 '03.Kicking',...
%                 '06.Piercing Line',...
%                 '28&39.Harami&Marubozu'};
% nPattern = numel(Pattn);
% [ns,nd] = size(K(:,:,1));
% SigMat1 = false([ns,nd,nPattern]);
% for i=1:ns
%     Open = fliplr(K(i,:,1));
%     High = fliplr(K(i,:,2));
%     Low  = fliplr(K(i,:,3));
%     Close= fliplr(K(i,:,4));
%     Open = Open';
%     High = High';
%     Low = Low';
%     Close = Close';
%     if min(Low)==0
%         continue;
%     end
%     [bull, bear, neutral] = candlesticks(Open,High,Low,Close);
%     SC = [bull; bear; neutral];
%     for j = 1:nPattern
%         if ~isempty(SC{Pattn(j)})
%             M = false([1,nd]);
%             M(SC{Pattn(j)})=true;
%             SigMat1(i,:,j) = fliplr(M);
%         end
%     end     
% end
%% Manually Merge && 
% SigMat1(:,:,5) = SigMat1(:,:,5) & SigMat1(:,:,6);
% SigMat1=SigMat1(:,1,1:5);
% 
% % *******  Remove signal occur before yesterday  ********                   
%     tod = max(dk1_date(:,1));               % Latest date
%     dt = (tod - Kdate(:,1))>1;
%     SigMat1(dt,:,:) = false;
% % *******************************************************
% fflag = 1;
% for i=1:nPattern-1
%     if sum(sum(SigMat1(:,:,i)))==0
%         continue;
%     else
%         eval(['ssd',num2str(i), '= sigDate(SigMat1(:,:,',num2str(i),'),Kdate,corpList_S,0);']);
%         eval(['J = numel(ssd',num2str(i),')']);
%         fprintf('CP%d: %s: %d Selection(s).\n',i,PattnName{i},J);
%         for ii = 1:J
%             eval(['ssd',num2str(i),'{',num2str(ii),'}'])
%         end
%         
%         if fflag
%             % open a file for writing
%             fname = ['CandlePaternSimple-',datestr(tod),'.txt'];
%             fid = fopen(fname, 'w');
%             fflag = 0;
%         end
% 
%         % print a title, followed by a blank line
%         fprintf(fid,'CandlePatern: %s: %d Selection(s).\n\n',PattnName{i},J);
%         
%         % print values in column order
%         % two values appear on each row of the file
%         
%         
%         
%     end
% end
% fclose(fid);


%% And Save Selections


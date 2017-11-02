load corpList.mat;
%corpList_S=cell(size(corpList));
load MWORK_ENV.mat
cd(MWORK_ROOT)
cd .\webconn
fl = dir([pwd,'\fdata\S*.mat']);
flc=struct2cell(fl)';
fl_name=flc(:,1);
fl_time=flc(:,2);

M = length(fl_name);
for i=1:M
    try
        eval(['load',' ./fdata/',cell2mat(fl_name(i))]);
        a = cell2mat(fl_name(i));
        b = a(1:8);
        eval([b '=' b '(fts2mat(',b,'.Volume)>0);']);
        eval(['save',' ./fdata/',cell2mat(fl_name(i)),' ',b]);
    catch
        warning('Fail to fetch %s. (Loop ID: %d)).',cell2mat(fl_name(i)),i);
    continue;
    end
end
f2pub = dir('Algo*.m');
f2pub = {f2pub.name,'readme.m'};

for i = 1:length(f2pub)
    clearvars -except i f2pub
    close all; clc
    file = publish(f2pub{i});
    web(file)
end

publish(f2pub{end},'pdf')
    
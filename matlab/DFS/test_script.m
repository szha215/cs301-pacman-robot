clear;
clc;
[m]=map_convert('map_1.txt');
plotmap(m);
tic
[m,v,s]=dfs('map_1.txt',[2,2],[6,2]);
plotmap(m,s);
toc
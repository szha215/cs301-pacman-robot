clear;
clc;
[m]=map_convert('map_8.txt');
plotmap(m);
[m,v,s]=dfs('map_8.txt',[14,1],[1,19]);
plotmap(m,s);
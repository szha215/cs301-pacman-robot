clear;
clc;

% viewmap('map_1.txt',0);
% [m]=map_convert('map_1.txt');
[m,v,s]=dfs('map_8.txt',[14, 1],[1, 18]);
plotmap(m,s)
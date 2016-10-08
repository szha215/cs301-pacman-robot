clear;
clc;
[m]=map_convert('map_8.txt');
plotmap(m);
tic
[m,v,s]=astar('map_8.txt',[14,1],[1,18]);
plotmap(m,s);
toc
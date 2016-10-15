clear;
clc;
[m]=map_convert('map_9.txt');
plotmap(m);
tic
[m,v,s]=astar('map_9.txt',[8,2],[6,17]);
plotmap(m,s);
toc
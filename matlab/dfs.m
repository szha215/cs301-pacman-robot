%% This is a shell that you will have to follow strictly. 
% You will use the plotmap() and viewmap() to display the outcome of your algorithm.

% Load sample_data_map_8, three variables will be created in your workspace. These were created as a 
% result of [m,v,s]=dfs('map_8.txt',[14,1],[1,18]);
% The solution can be viewed using 
% plotmap(m,s) 

% write your own function for the DFS algorithm.
function [retmap,retvisited,retsteps] = dfs( mapfile,startlocation,targetlocation)
    mapMatrix = map_convert(mapfile);
    msize = size(mapMatrix);
    retmap = mapMatrix;
    retvisited = zeros(msize(1),msize(2));
    steps = startlocation;
    [retvisited,retsteps] = recursive_search(startlocation,targetlocation,retvisited,mapMatrix,steps);
end
%%TODO:
%%figure out how to store steps into a vector cuz recursion makes my life harder
%%also figure out why retvisited has no value either
function [v,s]  = recursive_search(currentlocation,targetlocation,visitedMatrix,mapMatrix,retsteps)
	if currentlocation == targetlocation
		%goal found
		visitedMatrix(currentlocation(1),currentlocation(2)) = 1;
		v = visitedMatrix;
		s = retsteps;
		disp('END')
		return;

	else
		visitedMatrix(currentlocation(1),currentlocation(2)) = 1;
		for i = 1:4
			nextlocation = go(currentlocation,i);
            % disp('here0')
			if mapMatrix(nextlocation(1),nextlocation(2)) == 0
				% disp('here1')
				if visitedMatrix(nextlocation(1),nextlocation(2)) == 0
					% disp('here2')
					retsteps = [retsteps;nextlocation(1) nextlocation(2)];
					disp(nextlocation)	
					[visitedMatrix,retsteps] = recursive_search(nextlocation,targetlocation,visitedMatrix,mapMatrix,retsteps);
					v = visitedMatrix;
					s = retsteps;
                    if visitedMatrix(targetlocation(1),targetlocation(2)) == 1
                        return 
                    end
                     
                end
            end 
        end
	end
	v = visitedMatrix;
	s = retsteps;
end 



function nextlocation = go(currentlocation,direction)
	nextlocation = currentlocation;
    if nextlocation(1) > 1
        if direction == 1 %%north
            nextlocation(1) = nextlocation(1) - 1;
        end
    end

    if nextlocation(2) > 1 
        if direction == 3 %%west
            nextlocation(2) = nextlocation(2) - 1;
        end
    end 

   	if direction == 2 %%south
            nextlocation(1) = nextlocation(1) + 1;
    end

    if direction == 4 %%east
            nextlocation(2) = nextlocation(2) + 1;
    
    end
end
    
       



function placestep(position,i)
% This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
position = [16-position(1) position(2)];
position = [position(2)+0.1 position(1)+0.1];
rectangle('Position',[position,0.8,0.8],'FaceColor','y');
c = sprintf('%d',i);
text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end

%% This is a shell that you will have to follow strictly. 
% You will use the plotmap() and viewmap() to display the outcome of your algorithm.

% Load sample_data_map_8, three variables will be created in your workspace. These were created as a 
% result of [m,v,s]=dfs('map_8.txt',[14,1],[1,18]);
% The solution can be viewed using 
% plotmap(m,s) 

% write your own function for the DFS algorithm.
function [retmap,retvisited,retsteps] = dfs(mapfile,startlocation,targetlocation)
    mapMatrix = map_convert(mapfile);
    msize = size(mapMatrix);
    retmap = mapMatrix;
    retvisited = ones(msize(1),msize(2));
    steps = startlocation;
    if startlocation(1) < 1 || startlocation(2) < 1 || startlocation(1) > msize(1) || startlocation(2) > msize(2)
        error('Please enter a starting location that is not outside the map boundaries'); 
    end
    if (mapMatrix(startlocation(1),startlocation(2)) == 1)
        error('Please enter a starting location that is not in the wall'); 
    end
    if targetlocation(1) < 1 || targetlocation(2) < 1 || targetlocation(1) > msize(1) || targetlocation(2) > msize(2)
        error('Please enter a target location that is not outside the map boundaries'); 
    end
    if (mapMatrix(targetlocation(1),targetlocation(2)) == 1)
        error('Please enter a target location that is not in the wall'); 
    end
    [retvisited,retsteps] = recursive_search(startlocation,targetlocation,retvisited,mapMatrix,steps);
end

%This function will be recursively run until the target location is reached
function [v,s]  = recursive_search(currentlocation,targetlocation,visitedMatrix,mapMatrix,retsteps)
    %if target location is reached, return to dfs function with outputs
	if currentlocation == targetlocation
		%goal found
		visitedMatrix(currentlocation(1),currentlocation(2)) = 0;
		v = visitedMatrix;
		s = retsteps;
		disp('END')
		return;
    %else keep searching through the maze applying our direction priorities
	else
		visitedMatrix(currentlocation(1),currentlocation(2)) = 0;
		for i = 1:4 %for the four different possible directions
			nextlocation = nextBlock(currentlocation,i,mapMatrix);
            if visitedMatrix(nextlocation(1),nextlocation(2)) == 1 %If the next block has not been visited before
                if mapMatrix(nextlocation(1),nextlocation(2)) == 0 %If the next block is not a wall
					retsteps = [retsteps;nextlocation(1) nextlocation(2)];
					disp(nextlocation)	
					[visitedMatrix,retsteps] = recursive_search(nextlocation,targetlocation,visitedMatrix,mapMatrix,retsteps);
					v = visitedMatrix;
					s = retsteps;
                    if visitedMatrix(targetlocation(1),targetlocation(2)) == 0
                        return; 
                    end  
                end
            end 
        end
	end
	v = visitedMatrix;
	s = retsteps;
end 


%This function is run to find the next block to visited with specific
%direction priorities: North, East, South, West
function nextlocation = nextBlock(currentlocation,direction,mapMatrix)
	nextlocation = currentlocation;
    msize = size(mapMatrix);
    if direction == 1 && nextlocation(1) ~= 1    %%north
        nextlocation(1) = nextlocation(1) - 1;   
    elseif direction == 4 && nextlocation(2) ~= 1   %%west
        nextlocation(2) = nextlocation(2) - 1;
    elseif direction == 3 && nextlocation(1) ~= msize(1) %%south
        nextlocation(1) = nextlocation(1) + 1;
    elseif direction == 2 && nextlocation(2) ~= msize(2) %%east
        nextlocation(2) = nextlocation(2) + 1;
    end  
end

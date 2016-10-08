%AStar algorithm (sl = start location, tl = target location)
function [retmap,retvisited,retsteps] = astar(mapfile,sl,tl)
    mapMatrix = map_convert(mapfile);
    msize = size(mapMatrix);
    retmap = mapMatrix;
    retvisited = ones(msize(1),msize(2));
    retsteps = [];

    if sl(1) < 1 || sl(2) < 1 || sl(1) > msize(1) || sl(2) > msize(2)
        error('Please enter a starting location that is not outside the map boundaries'); 
    end
    if (mapMatrix(sl(1),sl(2)) == 1)
        error('Please enter a starting location that is not in the wall'); 
    end
    if tl(1) < 1 || tl(2) < 1 || tl(1) > msize(1) || tl(2) > msize(2)
        error('Please enter a target location that is not outside the map boundaries'); 
    end
    if (mapMatrix(tl(1),tl(2)) == 1)
        error('Please enter a target location that is not in the wall'); 
    end
    
    %Open nodes
    Open = cell(1,1);
    OCount = 0;
    
    %Closed nodes
    Closed = cell(1,1);
    CCount = 0;
    
    %Nodes that are on the line/pathway
    Searchable = cell(1,1);
    SCount = 0;
    
    %A cell that will tell us the parent of the current node
    parent = cell(1,1);
    
    %2D array for G/F scores
    Gcost = zeros(msize(1),msize(2));
    Fcost = zeros(msize(1),msize(2));
    
    %Adding start location to Open cell
    OCount = OCount + 1;
    Open{OCount} = sl;
    
    %Calculating the G and F costs of the start location
    Gcost(sl(1),sl(2)) = 0;
    Fcost(sl(1),sl(2)) = Gcost(sl(1),sl(2)) + HCalc(sl,tl); 
    
    %Putting all pathway nodes on the Searchable array
    for i = 1:msize(1)
        for j = 1:msize(2)
            if mapMatrix(i,j) == 0
                SCount = SCount + 1;
                Searchable{SCount,1} = [i,j];
            end
        end
    end
    
    %While there are still nodes that are needed to be searched
    while ~cellfun('isempty',Open)
        
        %The next current is the one in the Open cell with lowest F cost
        current = nextCurrent(tl,Open,Fcost);
        
        %If the targetlocation is found, break out of the while loop
        if(current == tl)
            retvisited(current(1), current(2)) = 0;
            CCount = CCount + 1;
            Closed{CCount} = current;
            break;
        end

        % Remove the current node from the Open cell as evaluated
        for i = 1:numel(Open);
            if current == Open{i}
                Open(:,i) = [];
                OCount = OCount - 1;
                break;
            end
        end

        %Adding current node to the Closed cell and marked as visited
        CCount = CCount + 1;
        Closed{CCount} = current;
        retvisited(current(1),current(2)) = 0;

        %Find available adjacent nodes
        adjacents = adjacent(current,Searchable);
        adjCount = size(adjacents);
        
        for k = 1:adjCount(1)
            
            %If the adjacent node is already evaluated skip to next adj
            if inSet(adjacents(k,:),Closed) == 1
                continue;
            end
            
            %Updating the current G cost from start location
            currentGcost = Gcost(current(1),current(2)) + 1;
            
            %If the current adjacent node not in Open cell, add it in
            if inSet(adjacents(k,:),Open) == 0
                OCount = OCount + 1;
                Open{OCount} = adjacents(k,:);
            end
            
            %Set parent node and update the Costs
            parent{adjacents(k,1),adjacents(k,2)} = current;
            Gcost(adjacents(k,1),adjacents(k,2)) = currentGcost;
            Fcost(adjacents(k,1),adjacents(k,2)) = Gcost(adjacents(k,1),adjacents(k,2)) + HCalc(adjacents(k,:),tl);
        end
    end
    
    %Final loop to return the steps from start to target location
    if(current == tl)
        retsteps = [retsteps; current];
        while ~isequal(current,sl)
            current = cell2mat(parent(current(1),current(2)));
            retsteps = [retsteps; current];
            disp(current);
        end
        %Flip the retsteps array because we traced backed to the start from
        %the target location as that is how A star works
        retsteps = flipud(retsteps);
    else
        error('There is no solution to this maze'); 
    end
end

function current = nextCurrent(tl,Open,Fcost)
    [~,s] = size(Open);
    
    %First first code in the Open cell is set as the lowest 
    lowestF = Fcost(Open{1}(1),Open{1}(2));
    current = Open{1};
    
    % Go through all the nodes in the Open cell
    for i = 2:s
        % If this node has a smaller F cost than current lowerF, replace
        if(Fcost(Open{i}(1),Open{i}(2)) < lowestF)
            lowestF = Fcost(Open{i}(1),Open{i}(2));
            current = Open{i};
            % If the two F costs are equal then the one with lower
            % manhattan distance becomes the new next current
        elseif(Fcost(Open{i}(1),Open{i}(2)) == lowestF)
            if(HCalc(Open{i}, tl) <= HCalc(current, tl))
                lowestF = Fcost(Open{i}(1),Open{i}(2));
                current = Open{i};
            end
        end
    end
end

%This function chooses the next current location and updates Closed/Opens
function adjacents = adjacent(current,path)
    [k,~] = size(path);
    adjacents = [];
    
    for i = 1:k
        if path{i,1}(1) + 1 == current(1) && path{i,1}(2) == current(2) || path{i,1}(1) - 1 == current(1) && path{i,1}(2) == current(2) || path{i,1}(1) == current(1) && path{i,1}(2) + 1 == current(2) || path{i,1}(1) == current(1) && path{i,1}(2) - 1 == current(2)
            adjacents = [adjacents;path{i,1}];
        end
    end
end

% This function return 1 if the node is found in the cell, otherwise 0
function bool = inSet(node,cell)
    bool = 0;
    for i = 1:numel(cell)
        if(node == cell{i})
            bool = 1;
            break;
        else
            bool = 0;
        end
    end
end

%Calculates the manhattan distance between two coordinates
function H = HCalc(start,finish)
    H = abs(finish(1)-start(1)) + abs(finish(2)-start(2));  
end
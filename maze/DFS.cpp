#include <stack>
#include "DFS.hpp"
#include "maze.hpp"
#include "bitmanip.hpp"
#include <thread>
#include <vector>
#include <cstdint>
using std::stack;
typedef struct
{
    unsigned char x;
    unsigned char y;
    unsigned char dir;
} Dot_t;

static Dot_t currlocation;

void setwalls(char matrix[MAZESIZE][MAZESIZE], char x, char y)
{
    //std::cerr<< "Setting walls for position (" << static_cast<int>(x) << ", " << static_cast<int>(y) << ")" << std::endl;
    if (API::wallFront())
    {
        if (currlocation.dir == 'N')
        {
            //std::cerr<< "Setting North wall" << std::endl;
            setNorth(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting South wall" << std::endl;
            setSouth(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting East wall" << std::endl;
            setEast(&matrix[x][y], true);
        }
        else
        {
            //std::cerr<< "Setting West wall" << std::endl;
            setWest(&matrix[x][y], true);
        }
    }
    if (API::wallLeft())
    {
        if (currlocation.dir == 'N')
        {
            //std::cerr<< "Setting West wall (Left)" << std::endl;
            setWest(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting East wall (Left)" << std::endl;
            setEast(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting North wall (Left)" << std::endl;
            setNorth(&matrix[x][y], true);
        }
        else
        {
            //std::cerr<< "Setting South wall (Left)" << std::endl;
            setSouth(&matrix[x][y], true);
        }
    }
    if (API::wallRight())
    {
        if (currlocation.dir == 'N')
        {
            //std::cerr<< "Setting East wall (Right)" << std::endl;
            setEast(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting West wall (Right)" << std::endl;
            setWest(&matrix[x][y], true);
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting South wall (Right)" << std::endl;
            setSouth(&matrix[x][y], true);
        }
        else
        {
            //std::cerr<< "Setting North wall (Right)" << std::endl;
            setNorth(&matrix[x][y], true);
        }
    }
}

void move(char direction)
{
    // Calculate the difference in x and y coordinates
    int dx = 0, dy = 0;
    switch (direction)
    {
    case 'N':
        dy = 1;
        break;
    case 'S':
        dy = -1;
        break;
    case 'E':
        dx = 1;
        break;
    case 'W':
        dx = -1;
        break;
    }

    // Adjust the current location based on the direction
    currlocation.x += dx;
    currlocation.y += dy;

    // Determine the target direction based on the difference in coordinates
    char targetDir;
    if (std::abs(dx) > std::abs(dy))
    {
        // Move horizontally
        if (dx > 0)
        {
            targetDir = 'E'; // Move to the east
        }
        else
        {
            targetDir = 'W'; // Move to the west
        }
    }
    else
    {
        // Move vertically
        if (dy > 0)
        {
            targetDir = 'N'; // Move to the north
        }
        else
        {
            targetDir = 'S'; // Move to the south
        }
    }

    // Rotate the robot to face the target direction
    while (currlocation.dir != targetDir)
    {
        API::turnRight(); // Adjust the orientation to the right
        switch (currlocation.dir)
        {
        case 'N':
            currlocation.dir = 'E';
            break;
        case 'E':
            currlocation.dir = 'S';
            break;
        case 'S':
            currlocation.dir = 'W';
            break;
        case 'W':
            currlocation.dir = 'N';
            break;
        }
    }

    // Move forward
    API::moveForward();
}

void movetopoint(Dot_t input)
{
    //std::cerr<< "Moving to point("<<static_cast<int>(input.x)<<","<<static_cast<int>(input.y)<<") Current location: (" << static_cast<int>(currlocation.x) << ", " << static_cast<int>(currlocation.y) << ")" << std::endl;
    if (input.x == currlocation.x && input.y == currlocation.y)
    {
        //std::cerr<< "Already at the destination." << std::endl;
        return;
    }
    else if (input.x == currlocation.x && input.y == currlocation.y + 1)
    { // check if N
        //std::cerr<< "Moving North" << std::endl;
        move('N');
    }
    else if (input.x == currlocation.x - 1 && input.y == currlocation.y)
    { // check if W
        //std::cerr<< "Moving West" << std::endl;
        move('W');
    }
    else if (input.x == currlocation.x && input.y == currlocation.y - 1)
    { // check if S
        //std::cerr<< "Moving South" << std::endl;
        move('S');
    }
    else if (input.x == currlocation.x + 1 && input.y == currlocation.y)
    { // it's E
        //std::cerr<< "Moving East" << std::endl;
        move('E');
    }
    else
    {
        //std::cerr<<"None of the above"<<std::endl;
    }
}

/*
procedure DFS_iterative(G, v) is
    let S be a stack
    S.push(v)
    while S is not empty do
        v = S.pop()
        if v is not labeled as discovered then
            label v as discovered
            for all edges from v to w in G.adjacentEdges(v) do
                S.push(w)
*/
void DFS(char matrix[16][16])
{
    stack<Dot_t> tovisit;
    stack<Dot_t> path;
    currlocation = {0, 0, 'N'};
    tovisit.push(currlocation);
    while (!tovisit.empty())
    {
        // pop the first node to visit
        Dot_t pope = tovisit.top();
        while(closeVisited(matrix[pope.x][pope.y])){
            //std::cerr<<"to go: ("<<static_cast<int>(pope.x)<<","<<static_cast<int>(pope.y)<<")"<<std::endl;
            tovisit.pop();
            pope = tovisit.top();
        }
       
        movetopoint(pope);
        tovisit.pop();
        // Add debug prints to track the path of the traversal
        //std::cerr << "Visiting: (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;

        // Check if the current location has already been visited
        if (closeVisited(matrix[currlocation.x][currlocation.y])) {
            //std::cerr << "Already visited: (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
            // continue; // Skip this location if it's already visited
        }

        // Rest of your traversal logic goes here

        path.push(currlocation); // add vertex to path
        unsigned char pushed = 0;
        std::cerr << "Added to path: (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
        setwalls(matrix, currlocation.x, currlocation.y);
        setVisited(&matrix[currlocation.x][currlocation.y], true);
        API::setColor(currlocation.x, currlocation.y, 'b');
        
        // check all edges
        if (!closeNorth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y + 1]))
        {
            Dot_t idiot = {currlocation.x, currlocation.y + 1, 'N'};
            tovisit.push(idiot);
            pushed++;
            //std::cerr << "Added neighbor to the north: (" << static_cast<int>(idiot.x) << "," << static_cast<int>(idiot.y) << ")" << std::endl;
        }
        if (!closeEast(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x + 1][currlocation.y]))
        {
            Dot_t idiot = {currlocation.x + 1, currlocation.y, 'E'};
            tovisit.push(idiot);
            pushed++;
            //std::cerr << "Added neighbor to the east: (" << static_cast<int>(idiot.x) << "," << static_cast<int>(idiot.y) << ")" << std::endl;
        }
        if (!closeSouth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y - 1]))
        {
            Dot_t idiot = {currlocation.x, currlocation.y - 1, 'S'};
            tovisit.push(idiot);
            pushed++;
            //std::cerr << "Added neighbor to the south: (" << static_cast<int>(idiot.x) << "," << static_cast<int>(idiot.y) << ")" << std::endl;
        }
        if (!closeWest(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x - 1][currlocation.y]))
        {
            Dot_t idiot = {currlocation.x - 1, currlocation.y, 'W'};
            tovisit.push(idiot);
            pushed++;
            //std::cerr << "Added neighbor to the west: (" << static_cast<int>(idiot.x) << "," << static_cast<int>(idiot.y) << ")" << std::endl;
        }

        if (pushed > 1)
        { // multiple possibilities
            setMultiple(&matrix[currlocation.x][currlocation.y], true);
            API::setText(currlocation.x, currlocation.y, "M");
        }
        else
        {
            char buf[10];
            sprintf(buf,"(%d,%d)",currlocation.x,currlocation.y);
            API::setText(currlocation.x, currlocation.y, buf);
            setMultiple(&matrix[currlocation.x][currlocation.y], false);
        }    
        if (pushed == 0)
        { // Implement backtracking
            Dot_t cagain = path.top();
            //std::cerr << "BACKTRACKING initiated from (" << static_cast<int>(cagain.x) << "," << static_cast<int>(cagain.y) << ")" << std::endl;
            while (!path.empty() && !hasMultiple(matrix[cagain.x][cagain.y]))
            {
                cagain = path.top();
                //std::cerr << "Currently at: (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
                movetopoint(cagain);
                if (hasMultiple(matrix[cagain.x][cagain.y]))
                {
                    std::cerr << "Multiple paths found at (" << static_cast<int>(cagain.x) << "," << static_cast<int>(cagain.y) << "). Exiting backtracking." << std::endl;

                    // Check if they've been visited already
                    // Check north:
                    bool North = !closeNorth(matrix[cagain.x][cagain.y]) && !closeVisited(matrix[cagain.x][cagain.y + 1]);
                    bool East = !closeEast(matrix[cagain.x][cagain.y]) && !closeVisited(matrix[cagain.x + 1][cagain.y]);
                    bool South = !closeSouth(matrix[cagain.x][cagain.y]) && !closeVisited(matrix[cagain.x][cagain.y - 1]);
                    bool West = !closeWest(matrix[cagain.x][cagain.y]) && !closeVisited(matrix[cagain.x - 1][cagain.y]);
                    //std::cerr<<"N: "<<North<<", S: "<<South<<", E"<<East<<", W"<<West<<std::endl;
                    if (North || East || South || West)
                    {
                        //std::cerr << "Found unvisited neighbors. Exiting backtracking." << std::endl;
                        break;
                    }
                    else
                    {
                        //std::cerr << "All neighbors were visited, continuing backtracking" << std::endl;
                    }
                }
                //std::cerr<< "Moving to the next point." << std::endl;
                std::cerr << "Popped: (" << static_cast<int>(cagain.x) << "," << static_cast<int>(cagain.y) << ")" << std::endl;
                API::setColor(currlocation.x, currlocation.y, 'r');
                path.pop();
            }
            //std::cerr << "End of BACKTRACKING." << std::endl;
        }
    }
}

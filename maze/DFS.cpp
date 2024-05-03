#include <stack>
#include "DFS.hpp"
#include "maze.hpp"
#include "bitmanip.hpp"
#include "./stack.hpp"
#include <thread>
#include <vector>
#include <cstdint>


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
            API::setWall(x, y, 'n');
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting South wall" << std::endl;
            setSouth(&matrix[x][y], true);
            API::setWall(x, y, 's');
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting East wall" << std::endl;
            setEast(&matrix[x][y], true);
            API::setWall(x, y, 'e');
        }
        else
        {
            //std::cerr<< "Setting West wall" << std::endl;
            setWest(&matrix[x][y], true);
            API::setWall(x, y, 'w');
        }
    }
    if (API::wallLeft())
    {
        if (currlocation.dir == 'N')
        {
            //std::cerr<< "Setting West wall (Left)" << std::endl;
            setWest(&matrix[x][y], true);
            API::setWall(x, y, 'w');
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting East wall (Left)" << std::endl;
            setEast(&matrix[x][y], true);
            API::setWall(x, y, 'e');
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting North wall (Left)" << std::endl;
            setNorth(&matrix[x][y], true);
            API::setWall(x, y, 'n');
        }
        else
        {
            //std::cerr<< "Setting South wall (Left)" << std::endl;
            setSouth(&matrix[x][y], true);
            API::setWall(x, y, 's');
        }
    }
    if (API::wallRight())
    {
        if (currlocation.dir == 'N')
        {
            //std::cerr<< "Setting East wall (Right)" << std::endl;
            setEast(&matrix[x][y], true);
            API::setWall(x, y, 'e');
        }
        else if (currlocation.dir == 'S')
        {
            //std::cerr<< "Setting West wall (Right)" << std::endl;
            setWest(&matrix[x][y], true);
            API::setWall(x, y, 'w');
        }
        else if (currlocation.dir == 'E')
        {
            //std::cerr<< "Setting South wall (Right)" << std::endl;
            setSouth(&matrix[x][y], true);
            API::setWall(x, y, 'S');
        }
        else
        {
            //std::cerr<< "Setting North wall (Right)" << std::endl;
            setNorth(&matrix[x][y], true);
            API::setWall(x, y, 'n');
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
bool comparedots(Dot_t a, Dot_t b)
{
    return a.x == b.x && a.y == b.y;
}
bool incenter(){
    return (currlocation.x == 7 && (currlocation.y == 7 || currlocation.y == 8)) || ((currlocation.x == 8 && (currlocation.y == 7 || currlocation.y == 8)));
}


void DFS(char matrix[16][16]){
    bool centerfound = false;
    stack branch;
    stack location;
    currlocation = {0, 0, 'N'};
    location.push(currlocation);
    while (!location.Isempty()){
        // pop the first node to visit
        Dot_t pope = location.top();
        movetopoint(pope);
        setwalls(matrix, currlocation.x, currlocation.y);
        setVisited(&matrix[currlocation.x][currlocation.y], true);
        uint8_t connections = 0;
        if(incenter()){
            while(!location.Isempty()){
                setwalls(matrix,currlocation.x,currlocation.y);
                movetopoint(location.top());
                std::cerr<<"popping"<<static_cast<int>(location.top().x)<<","<<static_cast<int>(location.top().y)<<std::endl;
                location.pop();
            }
            return;
        }

        
        if (!closeNorth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y + 1]))
            connections++;
        if (!closeSouth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y - 1]))
            connections++;
        if (!closeEast(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x + 1][currlocation.y]))
            connections++;
        if (!closeWest(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x - 1][currlocation.y]))
            connections++;
        // multiple branches
        if (connections > 1){
            //std::cerr<<"branches ("<<static_cast<int>(currlocation.x)<<","<<static_cast<int>(currlocation.y)<<")"<<std::endl;
            branch.push(pope);
            //API::setColor(currlocation.x, currlocation.y, 'g');
        }
        else
        {
            //API::setColor(currlocation.x, currlocation.y, 'b');
        }

        // adds neighbors to stack
        if (!closeNorth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y + 1]))
        {
            Dot_t idiot = {currlocation.x, currlocation.y + 1, 'N'};
            //std::cerr << "pushing N (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
            location.push(idiot);
        }
        if (!closeSouth(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x][currlocation.y - 1]))
        {
            Dot_t idiot = {currlocation.x, currlocation.y - 1, 'S'};
            //std::cerr << "pushing S (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
            location.push(idiot);
        }
        if (!closeEast(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x + 1][currlocation.y]))
        {
            Dot_t idiot = {currlocation.x + 1, currlocation.y, 'E'};
            //std::cerr << "pushing E (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
            location.push(idiot);
        }
        if (!closeWest(matrix[currlocation.x][currlocation.y]) && !closeVisited(matrix[currlocation.x - 1][currlocation.y]))
        {
            Dot_t idiot = {currlocation.x - 1, currlocation.y, 'W'};
            //std::cerr << "pushing W (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ")" << std::endl;
            location.push(idiot);
        }
        if (connections == 0)
        {
backtrack:
            if (!branch.Isempty())
            {
                while (!comparedots(branch.top(), location.top()))
                {
                    Dot_t temp = location.top();
                    movetopoint(temp);
                    //std::cerr << "popping (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ") size:"<<static_cast<int>(location.size())<<std::endl;
                    location.pop();
                }
                branch.pop();
            }
            else
            {
                while (!location.Isempty())
                {
                    Dot_t temp = location.top();
                    movetopoint(temp);
                    //std::cerr << "popping (" << static_cast<int>(currlocation.x) << "," << static_cast<int>(currlocation.y) << ") size:"<<static_cast<int>(location.size())<<std::endl;
                    location.pop();
                }
            }
        }
    }
    //std::cerr << "DFS complete" << std::endl;
}
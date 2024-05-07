#include "BFS.hpp"
#include "stack.hpp"
#include <string.h>
#include "bitmanip.hpp"
#include <iostream>
#include "./API.h"
// NSEWB*MV <- bit ordering
//     ^ BFS visited bit

bool incenter(Dot_t currlocation)
{
    return (currlocation.x == 7 && (currlocation.y == 7 || currlocation.y == 8)) || ((currlocation.x == 8 && (currlocation.y == 7 || currlocation.y == 8)));
}
/*
 1  procedure BFS(G, root) is
 2      let Q be a queue
 3      label root as explored
 4      Q.enqueue(root)
 5      while Q is not empty do
 6          v := Q.dequeue()
 7          if v is the goal then
 8              return v
 9          for all edges from v to w in G.adjacentEdges(v) do
10              if w is not labeled as explored then
11                  label w as explored
12                  w.parent := v
13                  Q.enqueue(w)
*/
void BFS(char matrix[16][16]) {
    //std::cerr << "BFS starts" << std::endl;
    Dot_t parentmatrix[16][16];
    memset(parentmatrix, 0, sizeof(parentmatrix));
    Queue queue(260);
    Dot_t currlocation = {0, 0, 'N'};
    parentmatrix[0][0] = currlocation;
    queue.Enqueue(currlocation);
    
    while (!queue.IsEmpty()) {
        currlocation = queue.top();
        queue.Dequeue();
        API::setColor(currlocation.x, currlocation.y, 'r');
        //std::cerr << "Current Location: (" << static_cast<int>(currlocation.x) << ", " << static_cast<int>(currlocation.y) << ")" << std::endl;

        if (incenter(currlocation)) {
            stack path;
            path.push(currlocation);
            Dot_t parent = parentmatrix[currlocation.x][currlocation.y];
            while(parent.x != 0 || parent.y != 0){
               
                path.push(parent);
                Dot_t temp = parentmatrix[parent.x][parent.y];
                parent = temp;
            }
            path.push({0,0,'N'});
            while(!path.Isempty()){
                API::setColor(path.top().x,path.top().y,'b');
                movetopoint(path.top());
                path.pop();
            }
            return;
        }

        // Check neighbors
        ////std::cerr<<"BFs has visited?"<<Bisvisited(matrix[currlocation.x][currlocation.y + 1])<<std::endl; 
        if (!closeNorth(matrix[currlocation.x][currlocation.y]) &&
            closeVisited(matrix[currlocation.x][currlocation.y + 1]) &&
            !Bisvisited(matrix[currlocation.x][currlocation.y + 1])) { // North
            //std::cerr << "Adding North neighbor to queue." << std::endl;
            API::setColor(currlocation.x, currlocation.y + 1, 'g');
            Bsetvisited(&matrix[currlocation.x][currlocation.y + 1], true);
            parentmatrix[currlocation.x][currlocation.y + 1] = currlocation;
            Dot_t topush = {currlocation.x, currlocation.y + 1, 'n'};
            queue.Enqueue(topush);
        }
        if (!closeSouth(matrix[currlocation.x][currlocation.y]) &&
            closeVisited(matrix[currlocation.x][currlocation.y - 1]) &&
            !Bisvisited(matrix[currlocation.x][currlocation.y - 1])) { // South
            //std::cerr << "Adding South neighbor to queue." << std::endl;
            API::setColor(currlocation.x, currlocation.y - 1, 'g');
            Bsetvisited(&matrix[currlocation.x][currlocation.y - 1], true);
            parentmatrix[currlocation.x][currlocation.y - 1] = currlocation;
            Dot_t topush = {currlocation.x, currlocation.y - 1, 's'};
            queue.Enqueue(topush);
        }
        if (!closeEast(matrix[currlocation.x][currlocation.y]) &&
            closeVisited(matrix[currlocation.x + 1][currlocation.y]) &&
            !Bisvisited(matrix[currlocation.x + 1][currlocation.y])) { // East
            //std::cerr << "Adding East neighbor to queue." << std::endl;
            API::setColor(currlocation.x + 1, currlocation.y, 'g');
            Bsetvisited(&matrix[currlocation.x + 1][currlocation.y], true);
            parentmatrix[currlocation.x + 1][currlocation.y] = currlocation;
            Dot_t topush = {currlocation.x + 1, currlocation.y, 'e'};
            queue.Enqueue(topush);
        }
        if (!closeWest(matrix[currlocation.x][currlocation.y]) &&
            closeVisited(matrix[currlocation.x - 1][currlocation.y]) &&
            !Bisvisited(matrix[currlocation.x - 1][currlocation.y])) { // West
            //std::cerr << "Adding West neighbor to queue." << std::endl;
            API::setColor(currlocation.x - 1, currlocation.y, 'g');
            Bsetvisited(&matrix[currlocation.x - 1][currlocation.y], true);
            parentmatrix[currlocation.x - 1][currlocation.y] = currlocation;
            Dot_t topush = {currlocation.x - 1, currlocation.y, 'w'};
            queue.Enqueue(topush);
        }
    // std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
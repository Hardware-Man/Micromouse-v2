#include "./maze.hpp"
#include "./bitmanip.hpp"
#include "./DFS.hpp"
#include<string.h>


void initialize(char maze[MAZESIZE][MAZESIZE]) {

    // set borders for walls array
    for(int i = 0; i < 16; i++) {
        setSouth(&maze[i][0],true); // adds wall on south wall
        API::setWall(i,0,'s');
        setNorth(&maze[i][15],true); //north wall
        API::setWall(i,15,'n');
        setWest(&maze[0][i],true); //along west wall
        API::setWall(0,i,'w');
        setEast(&maze[15][i],true); //along east wall
        API::setWall(15,i,'e');
    }
}

void startmaze(){
    char maze[MAZESIZE][MAZESIZE];
    memset(maze,0,sizeof(maze));
    initialize(maze);
    DFS(maze);
}

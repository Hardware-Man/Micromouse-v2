#include "./maze.hpp"
#include "./bitmanip.hpp"
#include "./DFS.hpp"
#include<string.h>


void initialize(char maze[MAZESIZE][MAZESIZE]) {

    // set borders for walls array
    for(int i = 0; i < 16; i++) {
        setSouth(&maze[i][0],true); // adds wall on south wall
        setNorth(&maze[i][15],true); //north wall
        setWest(&maze[0][i],true); //along west wall
        setEast(&maze[15][i],true); //along east wall
    }
}

void startmaze(){
    char maze[MAZESIZE][MAZESIZE];
    memset(maze,0,sizeof(maze));
    initialize(maze);
    DFS(maze);
}

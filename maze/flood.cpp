#include "flood.h"
#include <iostream>
// #include "queue.h"
using namespace std;

// "Definition checked against [extern] declaration"
// char maze[N][N];
 
struct openCells walls[N][N];
configuration currentCfg;

void initialize() {
    // set current configuration to (0, 0) facing N
    currentCfg.x = 0;
    currentCfg.y = 0;
    currentCfg.dir = 'N';

    // set borders for walls array
    for(int i = 0; i < 16; i++) {
        walls[i][0].openS = false; // move along south wall
        walls[i][15].openN = false; // move along north wall
        walls[0][i].openW = false; // move along west wall
        walls[15][i].openE = false; // move along east wall
    }
}

void setwalls(int x, int y){
    openCells* wall = &walls[x][y];
    if(API::wallFront()){
        if(currentCfg.dir == 'N'){
            wall->openN = false;
        }
        else if(currentCfg.dir == 'S'){
            wall->openS = false;
        }
        else if(currentCfg.dir == 'E'){
            wall->openE = false;
        }
        else{
            wall->openW = false;
        }
    }
    if(API::wallLeft()){
        if(currentCfg.dir == 'N'){
            wall->openW = false;
        }
        else if(currentCfg.dir == 'S'){
            wall->openE = false;
        }
        else if(currentCfg.dir == 'E'){
            wall->openN = false;
        }
        else{
            wall->openS = false;
        }
    }
    if(API::wallRight()){
        if(currentCfg.dir == 'N'){
            wall->openE = false;
        }
        else if(currentCfg.dir == 'S'){
            wall->openW = false;
        }
        else if(currentCfg.dir == 'E'){
            wall->openS = false;
        }
        else{
            wall->openN = false;
        }
    }
}


void move(char direction) {
    char myarray[] = {'N','W','S','E','N','S','E','W','N'};
    int index = 0;
    switch(direction){
        case 'N':
            currentCfg.y++;
            break;
        case 'S':
            currentCfg.y--;
            break;
        case 'E':
            currentCfg.x++;
            break;
        case 'W':
            currentCfg.x--;
            break;
    }
    switch(currentCfg.dir){
        case 'N':
            index = 0;
            break;
        case 'W':
            index = 1;
            break;
        case 'S':
            index = 2;
            break;
        case 'E':
            index = 3;
            break;
    }
    char changed = 0;
    while(myarray[index] != direction){
        std::cerr << myarray[index] << " != " << direction << std::endl;
        API::turnLeft();
        std::cerr << "direction: " << myarray[index] << std::endl;
        changed = 1;
        // Increment index and handle wrap-around
        index = (index + 1); // Since there are 4 directions in myarray
    }
    currentCfg.dir = direction;
    API::moveForward();
}



configuration getCenter(configuration input){
    int x = input.x;
    int y = input.y;
    //bottom left quad
    if(x <= 7 && y <= 7){
        return {7, 7, '\0'};
    }
    else if(x <= 7 && y > 7){ //top left
        return {7,8, '\0'};
    }
    else if(x > 7 && y > 7){ //top right
        return {8,8,'\0'};
    }
    else{ //bottom right
        return {8,7,'\0'};
    }
}
char decision(double* array){
    char carray[] = {'S','N','W','E'};
    double min = INFINITY;
    int index;
    for(int i = 0; i < 4; i++){
        if(array[i] < min){
            min = array[i];
            index = i;
        }
    }
    return carray[index];
}
void runMaze(char goal) {
    

    int loopCondition = 1;
    while(loopCondition){
    setwalls(currentCfg.x,currentCfg.y);
        //find weight of available spaces
        
        //check if S wall is open
        double Sheur = 100.0;
        double Nheur = 100.0;
        double Wheur = 100.0;
        double Eheur = 100.0;
        if(walls[currentCfg.x][currentCfg.y].openS){
            configuration center = getCenter(currentCfg);
            int a = pow(abs(center.x - currentCfg.x),2);
            int b = pow(abs(currentCfg.y - 1 - center.y),2);
            double c = (double)a + (double)b;
            Sheur = sqrt(c);
        }
        //check if N wall is open
        if(walls[currentCfg.x][currentCfg.y].openN){
            configuration center = getCenter(currentCfg);
            int a = pow(abs(currentCfg.x - center.x),2);
            int b = pow(abs(currentCfg.y + 1 - center.y),2);
            double c = (double)a + (double)b;
            Nheur = sqrt(c);
        }
        // check if W wall is open
        if(walls[currentCfg.x][currentCfg.y].openW){
            configuration center = getCenter(currentCfg);
            int a = pow(abs(currentCfg.x - 1 - center.x),2);
            int b = pow(abs(currentCfg.y - center.y),2);
            double c = (double)a + (double)b;
            Wheur = sqrt(c);
        }
        // check if E wall is open
        if(walls[currentCfg.x][currentCfg.y].openE){
            configuration center = getCenter(currentCfg);
            int a = pow(abs(currentCfg.x + 1 - center.x),2);
            int b = pow(abs(currentCfg.y - center.y),2);
            double c = (double)a + (double)b;
            Eheur = sqrt(c);
        }
        std::cerr<<"Sheur:"<<Sheur<<"\nNheur:"<<Nheur<<"\nWheur:"<<Wheur<<"\nEheur:"<<Eheur<<std::endl;
        double myarray[] = {Sheur, Nheur, Wheur, Eheur};
        char mdecision = decision(myarray);
        move(mdecision);
    }
    
}


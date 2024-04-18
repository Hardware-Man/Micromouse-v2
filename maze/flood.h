#ifndef FLOOD_H
#define FLOOD_H
#pragma once


#include "API.h"
//#include "..\Motors.h"
#include<stack>
#include<algorithm>
#include<math.h>

//// variable declarations
const int N = 16; 


struct configuration {
    int x;
    int y;
    char dir;
};


struct openCells {
    bool openN = true; 
    bool openS = true;
    bool openE = true;
    bool openW = true;
};


//// function declarations
void initialize();
void flowElevation();
openCells checkOpenCells(configuration currentCfg);
void checkNeigboringOpen(configuration poppedCfg);
void move(char direction);
void invertMaze(char goal);
void mazePrintout();
void runMaze(char goal);
void backTrack();

#endif
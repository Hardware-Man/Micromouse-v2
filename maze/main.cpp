#include "maze.hpp"
#include<cstdio>
/**
*   main function
*   @arg argc number of arguments
*   @arg argv our arguments
*aeuaoeu
*/
int main(int argc, char** argv){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            char buffer[9];
            sprintf(buffer,"%d,%d",i,j);
            API::setText(i,j,buffer);
        }
    }
    startmaze();
    return 0;
}
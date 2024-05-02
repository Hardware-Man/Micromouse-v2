#include "bitmanip.hpp"
#include <iostream>

//NSEW**MV <- bit ordering
bool closeNorth(char input){
    return (input & 0b10000000) != 0; // Corrected bit position for north
}
bool hasMultiple(char input){
    return (input & 0b00000010) != 0; //checks second to last bit
}

bool closeSouth(char input){
    return (input & 0b01000000) != 0; // Corrected bit position for south
}

bool closeEast(char input){
    return (input & 0b00100000) != 0;
}

bool closeWest(char input){
    return (input & 0b00010000) != 0;
}//aoeuaoe

bool closeVisited(char input){
    return (input & 0b00000001) != 0; // Corrected bit position for visited
}

void setNorth(char* input, bool isopen){
    if(isopen){ // if we want to close
        if(!closeNorth(*input)){ // if it's open
            *input |= 0b10000000; // Use bitwise OR to set north
        }
    }
    else{
        if(closeNorth(*input)){ // if it's closed
            *input &= 0b01111111; // Use bitwise AND to clear north
        }
    }
}

void setMultiple(char* input, bool isopen){
    if(isopen){ // if we want to close
        if(!hasMultiple(*input)){ // if it's open
            *input |= 2; // Use bitwise OR to set north
        }
    }
    else{
        if(hasMultiple(*input)){ // if it's closed
            *input &= 0b11111101; // Use bitwise AND to clear north
        }
    }
}


void setSouth(char* input, bool isopen){
    if(isopen){ // if we want to close
        if(!closeSouth(*input)){ // if it's open
            *input |= 0b01000000; // Use bitwise OR to set south
        }
    }
    else{
        if(closeSouth(*input)){ // if it's closed
            *input &= 0b10111111; // Use bitwise AND to clear south
        }
    }
}

void setEast(char* input, bool isopen){
    if(isopen){ // if we want to close
        if(!closeEast(*input)){ // if it's open
            *input |= 0b00100000; // Use bitwise OR to set east
        }
    }
    else{
        if(closeEast(*input)){ // if it's closed
            *input &= 0b11011111; // Use bitwise AND to clear east
        }
    }
}

void setWest(char* input, bool isopen){
    if(isopen){ // if we want to close
        if(!closeWest(*input)){ // if it's open
            *input |= 0b00010000; // Use bitwise OR to set west
        }
    }
    else{
        if(closeWest(*input)){ // if it's closed
            *input &= 0b11101111; // Use bitwise AND to clear west
        }
    }
}

void setVisited(char* input, bool isopen){
    if(isopen){ // if visited
        if(!closeVisited(*input)){ // if it's open
            *input |= 0b00000001; // Use bitwise OR to set visited
        }
    }
    else{
        if(closeVisited(*input)){ // if it's closed
            *input &= 0b11111110; // Use bitwise AND to clear visited
        }
    }
}

// /**
//  * test client code
//  */
// int main() {
//     char mazeCell = 0; // Initialize the maze cell

//     // Test setting and checking directions
//     // setNorth(&mazeCell, true);
//     setNorth(&mazeCell, false);
//     // setSouth(&mazeCell, true);
//     setSouth(&mazeCell, false);
//     setEast(&mazeCell, true);
//     // setEast(&mazeCell, false);
//     // setWest(&mazeCell, true);
//     setWest(&mazeCell, false);

//     std::cout << "North closed? " << closeNorth(mazeCell) << std::endl;
//     std::cout << "South closed? " << closeSouth(mazeCell) << std::endl;
//     std::cout << "East closed? " << closeEast(mazeCell) << std::endl;
//     std::cout << "West closed? " << closeWest(mazeCell) << std::endl;

//     // Test setting and checking visited
//     setVisited(&mazeCell, true);
//     std::cout << "Visited? " << closeVisited(mazeCell) << std::endl;

//     return 0;
// }

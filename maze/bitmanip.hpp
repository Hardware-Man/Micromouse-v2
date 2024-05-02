#ifndef BITMANIP_HPP
#define BITMANIP_HPP 
    //closeters
    bool closeNorth(char input);
    bool closeSouth(char inpu);
    bool closeEast(char input);
    bool closeWest(char input);
    bool closeVisited(char input);
    bool hasMultiple(char input);
    //setters

    void setNorth(char* input, bool isopen);
    void setSouth(char* input, bool isopen);
    void setEast(char* input, bool isopen);
    void setWest(char* input, bool isopen);
    void setVisited(char* input, bool isopen);
    void setMultiple(char* input, bool isopen);
#endif
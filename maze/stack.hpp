#ifndef STACK_HPP
#define STACK_HPP
#include "./structs.hpp"
class stack{
public:
    stack();
    ~stack();
    void push(Dot_t input);
    Dot_t top();
    void pop();
    bool Isempty();
    char size();
    bool exists(Dot_t input);
private:
  Dot_t* array; // Pointer to the array
  char index;
};
#endif
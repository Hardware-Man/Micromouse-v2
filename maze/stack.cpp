
#include "./structs.hpp"
#include "./stack.hpp"
#include <iostream>
/**
 * Stack constructor
*/
stack::stack()
{
    array = new Dot_t[256];
    index = 0;
}
stack::~stack()
{
    delete[] array;
}
void stack::push(Dot_t input)
{
    array[index++] = input;
}

bool stack::exists(Dot_t input){
    for(char i = 0; i < index; i++){
        if(array[i].x == input.x && array[i].y == input.y){
            return true;
        }
    }
    return false;
}
Dot_t stack::top()
{
    return array[index - 1];
}
void stack::pop()
{
    index--;
}
char stack::size(){
    return index;
}
bool stack::Isempty()
{
    return index == 0;
}

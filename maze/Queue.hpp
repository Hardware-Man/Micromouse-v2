#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "./structs.hpp"
class Queue{
    public:
        Queue(unsigned short size);
        ~Queue();
        void Enqueue(Dot_t data);
        Dot_t top();
        unsigned short getsize();
        bool IsEmpty();
        void Dequeue();
    private:
        Dot_t* array;
        unsigned short size;
        unsigned short head;
        unsigned short tail;
};
#endif
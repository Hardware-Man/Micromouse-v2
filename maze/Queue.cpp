#include "./structs.hpp"
#include "./Queue.hpp"

    Queue::Queue(unsigned short size){
        array = new Dot_t[size];
        this->head = this->tail = 0;
        this->size = size;
    }
    Queue::~Queue(){
        delete[] array;
    }
    void Queue::Enqueue(Dot_t data){
        array[tail++] = data;
        tail = tail % size;
        size++;
    }
    void Queue::Dequeue(){
        head++;
        head = head % size;
        size--;
    }
    Dot_t Queue::top(){
        return array[head];
    }
    unsigned short Queue::getsize(){
        return size;
    }
    bool Queue::IsEmpty(){
        return size == 0;
    }
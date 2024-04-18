#include "queue.h"

void enqueue(struct configuration input){
    queue[last++] = input;
    last = last % queuesize;
    size++;
}

struct configuration dequeue(){
    struct configuration toreturn = queue[first++];
    first = first % queuesize;
    size--;
    return toreturn;
}
bool queueisempty(){
    return size == 0;
}
void resetqueue(){
    first = 0;
    last = 0;
    size = 0;
}
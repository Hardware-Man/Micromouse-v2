#ifndef QUEUE_H
#define QUEUE_H
    #include "flood.h"
    const int queuesize = 100;
    struct configuration queue[queuesize];
    int first = 0;
    int last = 0;
    int size = 0;
    void enqueue(struct configuration input);
    bool queueisempty();
    struct configuration dequeue();
    void resetqueue();
#endif
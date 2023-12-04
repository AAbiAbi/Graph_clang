#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *q, void *data);
void *dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void freeQueue(Queue *q);

#endif

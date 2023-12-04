#include "queue.h"
#include <stdlib.h>

Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, void *data) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

void *dequeue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }

    QueueNode *temp = q->front;
    void *data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return data;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void freeQueue(Queue *q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

#ifndef QUEUE_H
#define QUEUE_H

#include <lcom/lcf.h>
typedef struct {
    int front, back, size;
    int capacity;
    int *array;
} Queue;

Queue *createQueue(int capacity);
int isFull(Queue *queue);
int isEmpty(Queue *queue);
void push(Queue *queue, uint item);
int pop(Queue *queue);
int front(Queue *queue);
int back(Queue *queue);
void deleteItems(Queue *queue);
int size(Queue *queue);

#endif

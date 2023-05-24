#include <lcom/lcf.h>
#include "queue.h"

Queue *createQueue(int capacity){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->back = capacity - 1;
    queue->array = (int *) malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue *queue){
    return (queue->size == queue->capacity);
}

int isEmpty(Queue *queue){
    return (queue->size == 0);
}

void push(Queue *queue, uint item){
    if(isFull(queue))
        return;
    queue->back = (queue->back + 1) % queue->capacity;
    queue->array[queue->back] = item;
    queue->size++;
}

int pop(Queue *queue){
    if(isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int front(Queue *queue){
    if(isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

int back(Queue *queue){
    if(isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->back];
}

void deleteItems(Queue *queue){
    free(queue->array);
    free(queue);
}

int size(Queue *queue){
    return queue->size;
}

#include "Queue.h"

void push(struct Queue *queue, void *data, int data_type, int size) {
    queue->list.insert(&queue->list, queue->list.length, data, data_type, size);
}

void *pop(struct Queue *queue) {
    void *data = queue->list.retrive(&queue->list, 0);
    queue->list.remove(&queue->list, 0);
    return data;
}


struct Queue queue_constructor(){
    struct Queue queue;

    queue.list = linkedList_constructor();

    queue.push = push;
    queue.pop = pop;
    

    return queue;
};
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include "../Common/Node.h"
#include<stdio.h>

struct LinkedList
{
    struct Node *head;
    int length;

    void (*insert)( struct LinkedList *linked_list,int index,void* data,int size);
    void (*remove)( struct LinkedList *linked_list,int index);
    void *(*retrive)(struct LinkedList *linked_list,int index);
    
    struct LinkedList (*constructor)(void);
};

//struct Node_int *iterate(int index,struct *LinkedList_int linked_list);

// void insert_node_int(int index ,int data, struct LinkedList_int *linked_list);
// void remove_node_int(int index, struct LinkedList_int *linked_list);
// int retrive_data_int(int index, struct LinkedList_int *linked_list);

struct LinkedList linkedList_constructor(void);
void linked_list_destructor(struct LinkedList *linked_list); 


#endif
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include "Node.h"
#include<stdio.h>

struct LinkedList_int
{
    struct Node *head;
    int length;

    void (*insert)(int index,int data, struct LinkedList_int *linked_list);
    void (*remove)(int index, struct LinkedList_int *linked_list);

    int (*retrive)(int index,struct LinkedList_int *linked_list);
    struct LinkedList_int (*constructor)(void);
};

//struct Node_int *iterate(int index,struct *LinkedList_int linked_list);

// void insert_node_int(int index ,int data, struct LinkedList_int *linked_list);
// void remove_node_int(int index, struct LinkedList_int *linked_list);
// int retrive_data_int(int index, struct LinkedList_int *linked_list);

struct LinkedList_int linkedList_int_constructor(); 


#endif
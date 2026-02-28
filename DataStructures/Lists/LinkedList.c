#include "LinkedList.h"

struct Node *create_node(void *data, int size) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
}

void destroy_node(struct Node *node_to_destroy) {
    node_destructor(node_to_destroy);
}

struct Node *iterate(struct LinkedList *linked_list, int index) {
    if(index < 0 || index >= linked_list->length) {
        printf("Index out of bound\n");
        exit(9);
    }
    struct Node *cursor = linked_list->head;
    for(int i = 0; i < index; i++) {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_node(struct LinkedList *linked_list, int index, void *data, int size) {
    struct Node *node_to_insert = create_node(data, size);

    if(index == 0) {
        node_to_insert->next = linked_list->head;
        linked_list->head = node_to_insert;
    } else {
        struct Node *cursor = iterate(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }

    linked_list->length += 1;
}

void remove_node(struct LinkedList *linked_list, int index) {
    if(index == 0) {
        struct Node *node_to_remove = linked_list->head;
        linked_list->head = node_to_remove->next;
        destroy_node(node_to_remove);
    } else {
        struct Node *cursor = iterate(linked_list, index - 1);
        struct Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node(node_to_remove);
    }

    linked_list->length -= 1;
}

void *retrive_data(struct LinkedList *linked_list, int index) {
    struct Node *cursor = iterate(linked_list, index);
    return cursor->data;
}

struct LinkedList linkedList_constructor() {
    struct LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_node;
    new_list.remove = remove_node;
    new_list.retrive = retrive_data;
    new_list.constructor = linkedList_constructor;

    return new_list;
}

void linked_list_destructor(struct LinkedList *linked_list) {
    struct Node *current = linked_list->head;
    while(current) {
        struct Node *next = current->next;
        destroy_node(current);
        current = next;
    }

    linked_list->head = NULL;
    linked_list->length = 0;
}

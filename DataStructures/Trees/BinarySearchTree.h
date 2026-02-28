#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "../Common/Node.h"

struct BinarySearchTree{
    struct Node *head;

    int (*compare)(void *data_one,void* data_two);
    void * (*search)(struct BinarySearchTree *tree, void *data);
    void (*insert)(struct BinarySearchTree  *tree, void *data,int size);

};
struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one,void* data_two));

void binary_search_tree_destructor(struct BinarySearchTree *tree);

int binary_search_tree_int_compare(void *data_one,void *data_two);
int binary_search_tree_float_compare(void *data_one,void *data_two);
int binary_search_tree_char_compare(void *data_one,void *data_two);
int binary_search_tree_str_compare(void *data_one,void *data_two);


#endif
#include "BinarySearchTree.h"

void * search_bst(struct BinarySearchTree *tree, void *data);
void insert_bst(struct BinarySearchTree *tree, void *data,int size);
void destory_node_bst(struct Node *node);
void recursive_tree_destruction(struct Node *node);

struct Node *create_node_bst(void *data, int size) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    *new_node = node_constructor(data, size);
    return new_node;
};

void destroy_node_bst(struct Node *node_to_destroy) {
    node_destructor(node_to_destroy);
}

struct BinarySearchTree binary_search_tree_constructor(int (*compare)(void *data_one,void* data_two)){

    struct BinarySearchTree tree;
    tree.compare = compare;
    tree.search = search_bst;
    tree.insert = insert_bst;
    return tree;
};

void binary_search_tree_destructor(struct BinarySearchTree tree){
recursive_tree_destruction(tree.head);
}

struct Node *iterate(struct BinarySearchTree *tree,struct Node *cursor,void *data, int *direction ){

    if(tree-> compare(cursor->data,data)== 1){
        if(cursor->next){
          return iterate(tree,cursor->next,data,direction);
        }else{
            *direction = 1;
            return cursor;
        }
       
    }

   else if(tree->compare(cursor->data,data)==-1){
           if(cursor->prev){
          return iterate(tree,cursor->prev,data,direction);
        }else{
            *direction = -1;
            return cursor;
        }
    }else{
        *direction = 0;
        return cursor;
    }
};


void recursive_tree_destruction(struct Node *node){
    if(node->prev){
        recursive_tree_destruction(node->prev);
    }
    if(node->next){
        recursive_tree_destruction(node->next);
    }
    destory_node_bst(node);
}


void * search_bst(struct BinarySearchTree *tree, void *data){
    int *direction= NULL;
    struct Node *cursor = iterate(tree,tree->head,data, direction);
    if(*direction ==0){
        return cursor->data;
    }else{
        return NULL;
    }
}

void insert_bst(struct BinarySearchTree *tree, void *data,int size){
    if(!tree->head){
        tree->head = create_node_bst(data,size);
        return;
    }
    int *direction= NULL;
    struct Node *cursor = iterate(tree,tree->head,data,direction);
    if(*direction ==1){
        cursor->next = create_node(data,size);
    }else if(*direction==-1){
        cursor->prev = create_node(data,size);
    }


}

//free_nodes my addition

void free_nodes(struct Node *node){
    if(!node) return;
    free_nodes(node->prev);
    free_nodes(node->next);
    destroy_node_bst(node);
}

void binary_search_tree_destructor(struct BinarySearchTree *tree){
    free(tree->head); 
    tree->head = NULL;
};

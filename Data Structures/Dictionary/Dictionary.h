#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../Trees/BinarySearchTree.h"
#include "Entry.h"

struct Dictionary {
    struct BinarySearchTree binary_search_tree;
    void (*insert)(struct Dictionary *dictionary, void *key, int key_size, void *value, int value_size);
    void *(*search)(struct Dictionary *dictionary, void *key, int value_size);   // ✅ return void*
};


struct Dictionary dictionary_constructor(int (*compare)(void *data_one, void *data_two));

void dictionary_destructor(struct Dictionary *dictionary);       // fixed: return void
int compare_string_keys(void *entry_one, void *entry_two);

#endif

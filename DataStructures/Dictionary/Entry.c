#include "Entry.h"
#include <stdlib.h>
#include<string.h>

struct Entry entry_constructor(void *key, int key_size, void *value, int value_size){

struct Entry entry;
    entry.key = malloc(key_size);
    entry.value = malloc(value_size);

    memcpy(entry.key,key,key_size);
    memcpy(entry.value,value,value_size);

return entry;

};


void entry_destructor(struct Entry *entry){
    free(entry->key);
    free(entry->value);
    free(entry);
};






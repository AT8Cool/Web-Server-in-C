#ifndef Entry_h
#define Entry_h

struct Entry{
    void *key;
    void *value;
};

struct Entry entry_constructor(void *key, int key_size, void *value, int value_size);

void entry_destructor(struct Entry *entry);



#endif
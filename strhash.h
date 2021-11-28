#ifndef __STRHASH
#define __STRHASH

#include "list.h"

typedef struct _hash_node s_hash;
struct _hash_node {
    s_node ** nodes;
    int size;
};

s_hash * hash_create(int size);

s_hash * hash_destroy(s_hash * hash_table);

s_hash * hash_append(s_hash * hash_table, void * data);

s_hash * hash_remove(s_hash * hash_table, void * data);

void hash_stats(s_hash * hash_table);

#endif
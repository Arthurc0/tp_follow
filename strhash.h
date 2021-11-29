#ifndef __STRHASH
#define __STRHASH

#include "list.h"

typedef struct _nodes_list s_list;
struct _nodes_list {
    s_node * head;
    int nodes_number;
};

typedef struct _hash_table s_hash;
struct _hash_table {
    s_list * lists;
    int size;
};

s_hash * hash_create(int size);

s_hash * hash_destroy(s_hash * hash_table);

s_hash * hash_append(s_hash * hash_table, char * data);

s_hash * hash_remove(s_hash * hash_table, char * data);

void hash_stats(s_hash * hash_table);

#endif
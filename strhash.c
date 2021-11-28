#include <stdlib.h>
#include "strhash.h"
#include "list.h"

s_hash * hash_create(int size) {
    s_hash * hash_table;
    hash_table = (s_hash *)malloc(sizeof(s_hash));
    hash_table->size = size;
    hash_table->nodes = (s_node **)malloc(size * sizeof(s_node));
    return hash_table;
}

s_hash * hash_destroy(s_hash * hash_table) {
    for(int i = 0; i < hash_table->size; i++) {
        while(hash_table->nodes[i] != NULL) {
            hash_table->nodes[i] = list_headRemove(hash_table->nodes[i]);
        }
    }
    hash_table->nodes = NULL;
    hash_table = NULL;

    return hash_table;
}

s_hash * hash_append(s_hash * hash_table, void * data) {
    int hash_key(char * str) {
        int key = 0;
        for(int i = 0; str[i] != '\0'; i++) {
            key = key * 2;
            key = key + str[i];
        }
        key = (key % hash_table->size);
        return key;
    }

    char * str_data = (char *)data;
    
    int key = hash_key(str_data);
    hash_table->nodes[key] = list_orderedAppend(hash_table->nodes[key], &compare_node, data);
    
    return hash_table;
}

s_hash * hash_remove(s_hash * hash_table, void * data) {
    
}

void hash_stats(s_hash * hash_table) {
    
}
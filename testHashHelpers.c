#include <stdio.h>
#include "strhash.h"
#include "testListHelpers.h"

void print_hash(s_hash * hash_table) {
    for(int i = 0; i < hash_table->size; i++) {
        printf("%d   (%d noeuds) : \n%s\n\n", i+1, hash_table->lists[i].nodes_number, list_to_string(hash_table->lists[i].head, node_int_to_string));
    }
    printf("\n");
}
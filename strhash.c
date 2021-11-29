#include <stdlib.h>
#include "strhash.h"
#include "list.h"

s_hash * hash_create(int size) {
    s_hash * hash_table;
    hash_table = (s_hash *)malloc(sizeof(s_hash));
    hash_table->size = size;
    hash_table->lists = (s_list *)malloc(size * sizeof(s_list));

    for(int i = 0; i < hash_table->size; i++) {
        hash_table->lists[i].head = list_create();
        hash_table->lists[i].nodes_number = 0;
    }
    
    return hash_table;
}

s_hash * hash_destroy(s_hash * hash_table) {
    for(int i = 0; i < hash_table->size; i++) {
        hash_table->lists[i].head = list_destroy(hash_table->lists[i].head);
    }
    
    hash_table->lists = NULL;
    hash_table = NULL;
    
    return hash_table;
}

static int hash_key(char * str, int size) {
    int key = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        key = key * 2;
        key = key + str[i];
    }
    key = (key % size);
    return key;
}

s_hash * hash_append(s_hash * hash_table, char * data) {
    int key = hash_key(data, hash_table->size);

    if(hash_table->lists[key].head->data == NULL) {
        hash_table->lists[key].head = list_insert(hash_table->lists[key].head, data);
        hash_table->lists[key].nodes_number++;
    } else {
        s_node * list = hash_table->lists[key].head;
        list = list_remove(list, data);
        
        // Si la donnée n'existe pas
        if(list == hash_table->lists[key].head) {
            hash_table->lists[key].nodes_number++;
        }
        hash_table->lists[key].head = list_orderedAppend(hash_table->lists[key].head, &compare_node, data);
    }

    return hash_table;
}

s_hash * hash_remove(s_hash * hash_table, char * data) {
    int key = hash_key(data, hash_table->size);
    hash_table->lists[key].head = list_remove(hash_table->lists[key].head, data);
    hash_table->lists[key].nodes_number--;
    return hash_table;
}

void hash_stats(s_hash * hash_table) {
    // Afficher des données statistiques concernant la table de hachage (nombre total d'éléments / nombre minimum et maximum d'éléments par entrée, écart-type du nombre d'éléments par entrée)
}
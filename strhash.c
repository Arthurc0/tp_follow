#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

void hash_destroy(s_hash * hash_table) {
    for(int i = 0; i < hash_table->size; i++) {
        free(hash_table->lists[i].head);
        //test destroy
        //hash_table->lists[i].head = list_destroy(hash_table->lists[i].head);
    }
    free(hash_table);
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
        // Si la donnée n'existe pas
        if(!data_exists(hash_table->lists[key].head, data)) {
            hash_table->lists[key].nodes_number++;
        }
        hash_table->lists[key].head = list_orderedAppend(hash_table->lists[key].head, &compare_node, data);
    }

    return hash_table;
}

s_hash * hash_remove(s_hash * hash_table, char * data) {
    int key = hash_key(data, hash_table->size);
    
    if(data_exists(hash_table->lists[key].head, (void *)data)) {
        hash_table->lists[key].nodes_number--;
    }
    
    hash_table->lists[key].head = list_remove(hash_table->lists[key].head, (void *)data);

    return hash_table;
}

void hash_stats(s_hash * hash_table) {
    int total;
    int min;
    int max;

    total = 0;
    min = 999;
    max = 0;

    for(int i = 0; i < hash_table->size; i++) {
        total += hash_table->lists[i].nodes_number;
        if(max < hash_table->lists[i].nodes_number) max = hash_table->lists[i].nodes_number;
        if(min > hash_table->lists[i].nodes_number && hash_table->lists[i].nodes_number != 0) min = hash_table->lists[i].nodes_number;
    }

    float moyenne = total / hash_table->size;
    float ecart_carre = 0;

    for(int i = 0; i < hash_table->size; i++) {
        ecart_carre += pow(hash_table->lists[i].nodes_number - moyenne, 2);
    }

    float ecart_type = sqrt(ecart_carre / hash_table->size);
    
    printf("Nombre total d'éléments : %d\n", total);
    printf("Nombre minimum d'éléments par entrée : %d\n", min);
    printf("Nombre maximum d'éléments par entrée : %d\n", max);
    printf("Ecart-type du nombre d'éléments par entrée : %f\n", ecart_type);
}
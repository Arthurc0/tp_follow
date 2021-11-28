#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "testListHelpers.h"
#include "strhash.h"

int main() {
    s_node * list = list_create();

    /*int i = 1;
    int j = 5;
    int k = 19;
    int l = 28;

    int m = 20;
    
    list_set_data(list, &i);

    list = list_append(list, &j);
    list = list_remove(list, &i);
    list = list_headRemove(list);
    list = list_append(list, &k);
    list = list_append(list, &l);
    list = list_orderedAppend(list, &compare_node, &m);
    
    */

    char * i = "salut";
    char * j = "non";
    char * k = "je";
    char * l = "ok";
    
    char * m = "ah";

    list_set_data(list, i);

    list = list_append(list, j);
    list = list_remove(list, i);
    list = list_headRemove(list);
    list = list_append(list, k);
    list = list_append(list, l);
    list = list_orderedAppend(list, &compare_node, m);

    char * list_string = list_to_string(list, &node_int_to_string);

    printf("%s\n", list_string);

    
    s_hash * hash = hash_create(5);
    printf("\n");
    printf("Nombre d'entrées : %d\n", hash->size);
    printf("Pointeur des noeuds : %p\n", hash->nodes);
    printf("Pointeur de la table de hachage (avant destroy) : %p\n", hash);

    hash = hash_append(hash, list->data);

    printf("%p\n", hash->nodes[3]);


    /*hash = hash_destroy(hash);
    printf("Pointeur de la table de hachage (après destroy) : %p\n", hash);*/
}
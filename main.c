#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "testListHelpers.h"
#include "testHashHelpers.h"
#include "strhash.h"

int main() {
    s_node * list = list_create();

    char * a = "a";
    char * b = "b";
    char * c = "c";
    char * d = "d";
    char * e = "e";

    printf("\n");
    
    list_set_data(list, a);
    printf("Initialiser a :    %s\n", list_to_string(list, node_int_to_string));

    list = list_append(list, b);
    printf("Append b :    %s\n", list_to_string(list, node_int_to_string));

    list = list_remove(list, a);
    printf("Remove a :    %s\n", list_to_string(list, node_int_to_string));
    
    list = list_headRemove(list);
    printf("Remove tête :    %s\n", list_to_string(list, node_int_to_string));
    
    list = list_append(list, c);
    list = list_append(list, d);
    printf("Append c et d :    %s\n", list_to_string(list, node_int_to_string));
    
    list = list_orderedAppend(list, &compare_node, e);
    list = list_orderedAppend(list, &compare_node, d);
    printf("Ordered Append e et d :    %s\n", list_to_string(list, node_int_to_string));
    
    list = list_remove(list, d);
    printf("Remove d :    %s\n", list_to_string(list, node_int_to_string));
    
    list = list_orderedAppend(list, &compare_node, d);
    printf("Ordered Append d :    %s\n", list_to_string(list, node_int_to_string));

    list = list_destroy(list);
    printf("Destroy :    %s\n", list_to_string(list, node_int_to_string));
    

    printf("\n");


    
    s_hash * hash = hash_create(5);
    printf("Nombre d'entrées : %d\n", hash->size);
    
    hash = hash_append(hash, "a");
    hash = hash_append(hash, "b");
    hash = hash_append(hash, "d");
    hash = hash_append(hash, "e");
    hash = hash_append(hash, "k");
    hash = hash_append(hash, "p");
    hash = hash_append(hash, "u");
    hash = hash_append(hash, "j");
    hash = hash_append(hash, "o");
    
    hash = hash_remove(hash, "b");
    //hash = hash_append(hash, "b");

    print_hash(hash);

    printf("%p\n", hash->lists[3].head);

    hash_stats(hash);
    /*
    hash = hash_destroy(hash);
    printf("Pointeur de la table de hachage (après destroy) : %p\n", hash);*/
}
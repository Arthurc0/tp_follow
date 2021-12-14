#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "testListHelpers.h"
#include "testHashHelpers.h"
#include "strhash.h"
#include "text.h"

int main() {

    //-- **************************  LISTE **************************

    /*s_node * list = list_create();

    char * a = "a";
    char * b = "b";
    char * c = "c";
    char * d = "d";
    char * e = "e";

    printf("\n");
    
    list_set_data(list, a);
    printf("Initialiser a :    %s\n", list_to_string(list));

    list = list_append(list, b);
    printf("Append b :    %s\n", list_to_string(list));

    list = list_remove(list, a);
    printf("Remove a :    %s\n", list_to_string(list));
    
    list = list_headRemove(list);
    printf("Remove tête :    %s\n", list_to_string(list));
    
    list = list_append(list, c);
    list = list_append(list, d);
    printf("Append c et d :    %s\n", list_to_string(list));
    
    list = list_orderedAppend(list, &compare_node, e);
    list = list_orderedAppend(list, &compare_node, d);
    printf("Ordered Append e et d :    %s\n", list_to_string(list));
    
    list = list_remove(list, d);
    printf("Remove d :    %s\n", list_to_string(list));
    
    list = list_orderedAppend(list, &compare_node, d);
    printf("Ordered Append d :    %s\n", list_to_string(list));

    list = list_destroy(list);
    printf("Destroy :    %s\n", list_to_string(list));
    

    printf("\n");*/

    //-- **************************  TABLE DE HACHAGE **************************
    /*
    s_hash * hash;

    int size_hash = 9;
    
    hash = hash_create(size_hash);
    
    printf("Create :\n\n");
    print_hash(hash);

    hash = hash_append(hash, "premier");
    hash = hash_append(hash, "deuxieme");
    hash = hash_append(hash, "troisieme");
    hash = hash_append(hash, "quatrieme");
    hash = hash_append(hash, "cinquieme");
    hash = hash_append(hash, "sixieme");
    hash = hash_append(hash, "septieme");
    hash = hash_append(hash, "huitieme");
    hash = hash_append(hash, "neuvieme");
    hash = hash_append(hash, "dixieme");
    hash = hash_append(hash, "onzieme");
    hash = hash_append(hash, "douzieme");
    hash = hash_append(hash, "treizieme");
    hash = hash_append(hash, "quatorzieme");
    hash = hash_append(hash, "quinzieme");
    hash = hash_append(hash, "seizieme");

    printf("Plusieurs append :\n\n");
    print_hash(hash);

    printf("Append déjà existant (septieme) :\n\n");
    hash = hash_append(hash, "septieme");
    print_hash(hash);

    printf("Remove existant (quatrieme) :\n\n");
    hash = hash_remove(hash, "quatrieme");
    print_hash(hash);

    printf("Remove inexistant (test) :\n\n");
    hash = hash_remove(hash, "test");
    print_hash(hash);

    printf("Statistiques :\n\n");
    hash_stats(hash);

    hash_destroy(hash);
    printf("Pointeur de la table de hachage (après destroy) : %p\n", hash);
    */

    //-- **************************  CHARGEMENT / ANALYSE DE TEXTES **************************
    char * text = load_text("test.txt");
    
    s_hash * hash;
    int size_hash = 9;
    hash = hash_create(size_hash);

    token ** tokens;
    tokens = tokenize_text(text, hash);
    
    print_hash(hash);
    hash_stats(hash);

    print_tokens(tokens);
}
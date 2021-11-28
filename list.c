#include "list.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// creation d'une nouvelle liste vide
s_node * list_create() {
    s_node * node;
    node = (s_node *)malloc(sizeof(s_node));
    node->data = NULL;
    node->next = NULL;
    return node;
}

// retourne la donnee d'un noeud
void * list_get_data(s_node * node) {
    return node->data;
}

// ecrire la donnee d'un noeud
void list_set_data(s_node * node, void * data) {
    node->data = data;
}

// creation et insertion d'un noeud en tete de liste
// retourne la tete de liste
s_node * list_insert(s_node * head, void * data) {
    if(head == NULL || list_get_data(head) == NULL) {
        free(head);
        head = list_create();
        list_set_data(head, data);
        head->next = NULL;
        return head;
    }

    s_node * node = list_create();
    list_set_data(node, data);
    node->next = head;
    return node;
}

// creation et ajout d'un noeud en queue de liste
// retourne la tete de liste
s_node * list_append(s_node * head, void * data) {
    if(head == NULL || list_get_data(head) == NULL) {
        free(head);
        head = list_create();
        list_set_data(head, data);
        head->next = NULL;
        return head;
    }

    s_node * current_node = head;

    while(current_node->next != NULL)
        current_node = current_node->next;

    s_node * last_node = list_create();
    list_set_data(last_node, data);
    current_node->next = last_node;

    return head;
}

int compare_node(s_node * node, void * data){
	const char *str1 = (char *)list_get_data(node);
	const char *str2 = (char *)data;

	return strcmp(str1, str2);
}

// ajout d'un noeud dans une liste ordonnee
// selon le resulat de "compare" ;
// si la donnee existe deja, elle n'est pas ajoutee
s_node * list_orderedAppend(s_node * head, int (*compare)(s_node *, void *), void *param){
    if(head != NULL) {
        s_node * previous_nodes = list_create();
        s_node * current = head;

        int list_initialized = 0;

        while((*compare)(current,param) < 0) {
            previous_nodes = list_append(previous_nodes, list_get_data(current));
            if(!list_initialized) list_initialized = 1;

            if(current->next != NULL)
                current = current->next;
            else break;
        }
		
        // Si le noeud à ajouter existe déjà
        if((*compare)(current,param) == 0) {
            free(previous_nodes);
            return head;
        }

        // Si le noeud doit être ajouté en tête de liste
        if(!list_initialized) {
            free(previous_nodes);
            return list_insert(head, param);
        }

        // Si le noeud doit être ajouté en queue de liste
        if(current->next == NULL && (*compare)(current,param) < 0)
            current = list_headRemove(current);
        
        current = list_insert(current, param);
        
        while(current != NULL) {
            previous_nodes = list_append(previous_nodes, list_get_data(current));
            current = current->next;
        }

        return previous_nodes;
    }
    return head;
}
/*
5 -> 7 -> 16 -> 28 -> null
        29
        current = 5 -> 7 -> 16 -> 28 -> null
        previous_nodes = 
*/


// suppression de la premiere instance d'une
// donnee dans la liste, retourne la tete de liste
s_node * list_remove(s_node * head, void * data) {
    s_node * current_node = head;

    if(list_get_data(current_node) == data) {
        head = head->next;
        free(current_node);
        return head;
    }
    
    s_node * previous_node;

    while(current_node != NULL && current_node->data != data) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if(current_node != NULL) {
        previous_node->next = current_node->next;
        free(current_node);
    }
    
    return head;
}

// suppression de la tete de liste
// retourne la nouvelle tete de liste
s_node * list_headRemove(s_node * head) {
    if(list_get_data(head) == NULL)
        return head;
    
    s_node * new_list = head->next;
    free(head);
    return new_list;
}

// destruction d'une liste
//  (La liberation des donnees n'est pas prise en charge)
s_node * list_destroy(s_node * head) {
    while(head != NULL)
        head = list_headRemove(head);
    
    return head;
}
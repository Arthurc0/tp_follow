#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "text.h"

char * load_text(char * filename) {
    FILE *file = fopen(filename, "r");
    
    if(file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }
    
    char * content = (char *)malloc(sizeof(char));
    
    int current_char;
    int char_counter;
    
    for(char_counter = 0; (current_char = fgetc(file)) != EOF; char_counter++) {
        content = realloc(content, (char_counter+1) * sizeof(char));
        content[char_counter] = (char)current_char;
    }
    fclose(file);
    content = realloc(content, (char_counter+1) * sizeof(char));
    content[char_counter] = '\0';

    return content;
}

token * create_token(enum type type, int offset, char * string) {
    token * tok = (token *)malloc(sizeof(token));
    tok->type = type;
    tok->textOffset = offset;

    if(type == WORD || type == SPACE)
        tok->data.word = string;
    if(type == SHORT_SPACE) {
        for(int i = 0; i < 4; i++) {
            tok->data.space[i] = string[i];
        }
    }
    
    return tok;
}

token ** tokenize_text(char * text, s_hash * hash_table) {
    if(text[0] == '\0')
        return NULL;
    token ** tokens = (token **)malloc(sizeof(token));
    int i = 0;
    int tokens_number = 0;

    while(text[i] != '\0') {
        token * token;
        int size = 0;
        
        // Tant que le caractère n'est pas un délimiteur
        while((text[i] != ' ' && text[i] != '\t' && text[i] != '\n') && text[i] != '\0') {
            i++;
            size++;
        }
        
        char * str;
        
        // Mot trouvé
        if(size > 0) {
            str = (char *)malloc((size + 1) * sizeof(char));
            for(int j = 0; j < size; j++)
                str[j] = text[i-size+j];
            str[size] = '\0';
            token = create_token(WORD, i-size, str);
        } else {
            // Tant que le caractère est un délimiteur
            while((text[i] == ' ' || text[i] ==  '\t' || text[i] == '\n') && text[i] != '\0') {
                i++;
                size++;
            }
            
            str = (char *)malloc((size + 1) * sizeof(char));
            
            // Zone blanche trouvée
            if(size > 4) {
                for(int j = 0; j < size; j++)
                    str[j] = text[i-size+j];
                str[size] = '\0';
                token = create_token(SPACE, i-size, str);
            }
            // Courte zone blanche trouvée
            else {
                for(int j = 0; j < size; j++)
                    str[j] = text[i-size+j];
                str[size] = '\0';
                token = create_token(SHORT_SPACE, i-size, str);
            }
        }
        
        hash_table = hash_append(hash_table, str);
        
        tokens = realloc(tokens, (tokens_number+1) * sizeof(token));

        tokens[tokens_number] = token;
        tokens_number++;
    }
    
    tokens = realloc(tokens, (tokens_number+1) * sizeof(token));
    tokens[tokens_number] = NULL;
    
    return tokens;
}

void delimiters_stats(char * str) {
    int tab_nb = 0;
    int newline_nb = 0;
    int space_nb = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\t')
            tab_nb++;
        else if(str[i] == '\n')
            newline_nb++;
        else if(str[i] == ' ')
            space_nb++;
    }
    if(tab_nb > 0) printf("  -> %d tabulation\n", tab_nb);
    if(newline_nb > 0) printf("  -> %d retour à la ligne\n", newline_nb);
    if(space_nb > 0) printf("  -> %d espace\n", space_nb);
}

void print_tokens(token ** tokens) {
    for(int i = 0; tokens[i] != NULL; i++) {
        printf("\n---------\n");
        printf("TOKEN %d\n", i+1);
        printf("---------\n\n");

        printf("Offset : %d\n", tokens[i]->textOffset);

        if(tokens[i]->type == WORD) {
            printf("Mot\n");
            printf("  -> %s\n", tokens[i]->data.word);
        } else if(tokens[i]->type == SHORT_SPACE) {
            printf("Courte zone blanche\n");
            delimiters_stats(tokens[i]->data.space);
        } else if(tokens[i]->type == SPACE) {
            printf("Zone blanche\n");
            delimiters_stats(tokens[i]->data.word);
        }
    }
    printf("\n");
}
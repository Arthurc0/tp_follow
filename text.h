#ifndef __TEXTH
#define __TEXTH

#include "strhash.h"

typedef struct _token token;
struct _token {
    enum type {
        WORD, SHORT_SPACE, SPACE, ERASE, INSERT, REPLACE, EMPTY
    } type;

    int textOffset;

    union {
        char * word;
        char space[4];
    } data;
};

char * load_text(char * filename);

token ** tokenize_text(char * text, s_hash * hash_table);

void delimiters_stats(char * str);

void print_tokens(token ** tokens);

#endif
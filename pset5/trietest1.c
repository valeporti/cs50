/**
 * trietest1.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * understand how pointers, structs and tries works by using debuger.
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
//for printing pointers
#include <inttypes.h>

//#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

bool load(const char* dictionary);
int asignar_num(char readchar);

typedef struct _trie
{
    int clave;
    struct _trie* letra[26];
}
trie;

typedef struct _prueba
{
    int uno;
    int dos;
    char cuatro[2];
}
prueba;

int main(int argc, char* argv[])
{
    //k = 3, el puntero pk iguala al puntero de k, hacia donde apunta pk es = 8 = k
    int k = 3;
    int* pk = &k;
    *pk = 8;
    
    //jugar con structs
    prueba* prueba1 = malloc(sizeof(prueba));
    prueba1->uno = 4;
    prueba1->dos = 6;
    prueba1->cuatro[1] = 'a';
    prueba1->cuatro[0] = 'b';
    
    //entender trie
    trie* root = malloc(sizeof(trie));
    root->clave = 0;
    root->letra[0] = NULL;
    //root->letra = NULL;
    if (root->letra[1] == NULL)
    {
        printf("si es null\n");
        printf("%p\n",root->letra[0] );
        printf("0x%" PRIXPTR "\n", (uintptr_t)root->letra[1] );
    }
    if (root->letra[0] == root->letra[1])
    {
        printf("YES\n");
    }
    
    trie* primer = malloc(sizeof(trie));
    root->letra[1] = primer;
    primer->clave = 1;
    
    
    free(prueba1);
    free(root);
    free(primer);
    
}

int asignar_num(char readchar)
{
    int modulo = (readchar - 'a') % 26;
    return modulo;
}


/**
 * trietest2.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * understand how trie works, in the level of making new ones or verifying existence in order to not mess with memory
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
    
    free(prueba1);
    
    /**
     * Entender trie con casos como simulacro de un loop
     */
    
    // declarar root (base para busqueda de trie)
    trie* root = malloc(sizeof(trie));
    root->clave = 0;
    trie* pri = NULL;
    trie* seg = NULL;
    
    for (int i = 10; i != 0; i = 10)
    {
        
        printf("coloca caso a entender (para terminar escribe 0): ");
        int n = GetInt();
        printf("\n");
        i=n;
        
        if(n == 1)
        {
            //caso donde se coloca ruta 0 - 1 - 1
            if (root->letra[n] == NULL)
            {
                pri = malloc(sizeof(trie));
                pri->clave = n;
                root->letra[n] = pri;
            }
            if (pri->letra[n] == NULL)
            {
                seg = malloc(sizeof(trie));
                seg->clave = n;
                pri->letra[n] = seg;
            }
            
        }
        else if (n == 2)
        {
            //caso donde se coloca ruta 0 - 1 - 2
            if (root->letra[1] == NULL)
            {
                pri = malloc(sizeof(trie));
                pri->clave = n;
                root->letra[n] = pri;
            }
            if  (root->letra[1]->clave == 1)
            {
                printf("se accedió a root->letra[1]->clave = 1");
            }
            
            if (pri->letra[n] == NULL)
            {
                seg = malloc(sizeof(trie));
                seg->clave = n;
                pri->letra[n] = seg;
            }
        }
        else if (n == 3)
        {
            //caso donde se coloca 0 - 2 - 2
        }
        else
        {
            printf("caso no existe\n");
        }
        
        //aqui es donde se pondría el free(root); si no se quisiera que quedar en memoria
    }
    
    //dibujar las cosas puestas en cada leaf of trie
    
}

int asignar_num(char readchar)
{
    int modulo = (readchar - 'a') % 26;
    return modulo;
}


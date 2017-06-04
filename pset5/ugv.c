/**
 * ugv.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * The sole intention of this program is to undertand how a variable works, speaking of scope
 * The interesting part to understand is how to manage that a variable (just like root = pointer to our core point where dictionary may be allocated)
 * stands for different functions such as check or load or unload
 */
 
 //PARECE   QUE YA SALIÓ.
 //EL VALOR SE MANTIENE AUNQUE NO SABRÍA DECIR BIEN POR QUÉ
 
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
//for printing pointers
#include <inttypes.h>

#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

trie* p (trie* k);
void func1(void);
void func2(void);

trie* pk = NULL;

typedef struct _prueba
{
    int uno;
    int dos;
    char cuatro[2];
}
prueba;

int main(void)
{

    func1();
    func2();
}

trie* p(trie* k)
{
    trie* ch = NULL;
    ch = k;
    if (k == NULL)
    {
        k = malloc(sizeof(trie));
    }
    else
    {
        k = pk;
    }
    ch =k;
    return k;
}

void func1(void)
{
    trie* ch = NULL;
    ch = pk;
    pk = p(pk);
    ch = pk;
    pk->clave = 8;
    //ch->clave = pk->clave;
}

void func2(void)
{
    trie* ch = NULL;
    ch = pk;
    pk = p(pk);
    ch = pk;
    ch->clave = pk->clave;
    pk->clave = 2 * pk->clave;
    ch->clave = pk->clave;
}
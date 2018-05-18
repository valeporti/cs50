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
 
 //NO SE POR QUÉ NO ME DEJA MANTENER EL VALOR DE PK, COMO QUE SI LO MANTIENE PERO SOLO AL FINAL
 //CUANDO SE LE DA EL VALOR DE 8 NO MANTIENE ESE VALOR
 
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
//for printing pointers
#include <inttypes.h>

//#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

bool func1(void);
bool func2(void);
int* p (int* k);

typedef struct _prueba
{
    int uno;
    int dos;
    char cuatro[2];
}
prueba;

int* pk = NULL;

int main(void)
{
    bool l = false;
    bool m = false;
    
    int* ch = pk;
    
    //printf("valor de pk antes función 0x%" PRIXPTR "\n", (uintptr_t)pk);
    ch=pk;
    l = func1();
    ch=pk;
    //printf("valor de pk después función 0x%" PRIXPTR "\n", (uintptr_t)pk);
    if (l)
    {
        printf("1 pk cambió de NULL a 8, comprobar: %i\n", *pk);
        ch = pk;
    }
    else
    {
        printf("fallido\n");
        ch = pk;
    }
    ch = pk;
    printf("2 pk cambió de NULL a 8, comprobar: %i\n", *pk);
    ch = pk;
    //printf("2 valor de pk antes función 0x%" PRIXPTR "\n", (uintptr_t)pk);
    m = func2();
    //printf("2 valor de pk después función 0x%" PRIXPTR "\n", (uintptr_t)pk);
    if (m)
    {
        printf("función2 pk salió: %i\n", *pk);
        printf("función2 ch salió: %i\n", *ch);
    }
    else
    {
        printf("fun2 no salió\n");
    }
    //printf("3 valor de pk al final 0x%" PRIXPTR "\n", (uintptr_t)pk);
}

bool func1(void)
{
    //k = 3, el puntero pk iguala al puntero de k, hacia donde apunta pk es = 8 = k
    if (pk == NULL)
    {
        int k = 3;
        pk = &k;
        *pk = 8;
        //printf("valor de pk en función 0x%" PRIXPTR "\n", (uintptr_t)pk);
        return true;
    }
    else
    {
        return false;
    }
}

bool func2(void)
{
    if (pk != NULL)
    {
        printf("valor desde func2 de *pk : %i\n", *pk);
        int* k = NULL;
        k = p(k);
        printf("valor desde func2 de *pk : %i\n", *pk);
        return true;
    }
    else
    {
        return false;
    }
}

int* p (int* k)
{
    printf("valor desde p de *pk : %i\n", *pk);
    if (k == NULL)
    {
        k = malloc(sizeof(int));
    }
    else
    {
        k = pk;
    }
    printf("valor desde p de *pk : %i\n", *pk);
    return k;
}
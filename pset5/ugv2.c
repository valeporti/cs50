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

//#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

int* p (int* k);
void func1(void);
void func2(void);

int* pk = NULL;

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

int* p(int* k)
{
    int* ch = NULL;
    ch = k;
    if (k == NULL)
    {
        k = malloc(sizeof(int));
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
    int* ch = NULL;
    ch = pk;
    pk = p(pk);
    ch = pk;
    *pk = 8;
    *ch = *pk;
}

void func2(void)
{
    int* ch = NULL;
    ch = pk;
    pk = p(pk);
    ch = pk;
    *ch = *pk;
    *pk = 2 * *pk;
    *ch = *pk;
}
/**
 * 2lkup.c
 *
 * Computer Science 50
 * Problem Set 6
 * lookup function
 *
 * The sole intention of this program is to undertand how const char* works
 * and dynamically allocate memory for array
 * 
 */
 
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
//for printing pointers
#include <inttypes.h>

const char* func1(const char* ruta);

int main(void)
{
    char path[6];
    for (int i = 0; i < 5; i ++)
    {
        path[i] = 'a'+ i;
    }
    path[2] = '.';
    path[5] = '\0';
    
    const char* type = func1(path);
    printf("%s\n", type);

}

const char* func1(const char* path)
{
    int largo = strlen(path);
    char extension[3];
    for (int index = 2, index2 = 0; index2 < 3; index --, index2 ++)
    {
        extension[index] = path[largo - 1 - index2];
    }
    printf("%s\n", extension);
    char l[4] = ".de";
    //Al parecer, char sí aplica el signo de "palabra terminada" automaticamente pero "const char" no, ni aunque se quiera incluir
    //por ello, con l[] no se puede pues es .,d,e,\0 y extension es .,d,e.
    //sin embargo quiero que el array extensión, el número de variables sea dinámica.
    printf("%s\n", l);
    int one = strcmp("l","l");//para entender cómo funciona la función "strcmp"
    int two = strcmp("a","l");
    int three = strcmp("z","l");
    printf("%i,%i,%i\n", one, two, three);
    
    char* point = strrchr(path,'.');
    int cuanto = strlen(point);
    printf("%i\n", cuanto);
    
    if (strcmp(point,".de")==0)
    {
        return ".de";
    }
    else if (strcasecmp(point,l)==0)
    {
        return "l";
    }
    else
    {
        return NULL;
    }
    
}


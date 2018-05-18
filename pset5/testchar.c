/**
 * tr.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * show how c reads characters from file
 */
 
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

bool load(const char* dictionary);
int asignar_num(char readchar);

int main(int argc, char* argv[])
{
    // determine dictionary to use
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    
    printf("%s\n", dictionary);

    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s!", dictionary);
        return false;
    }
    
    for (int c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        if (c == '\n')
        {
            printf("Space in ASCII is number %d\n", c);
        }
        else if (c == '\'')
        {
            printf("apostrophe %c in ASCII is number %d\n", c, c);            
        }
        else
        {
            printf("letter %c in ASCII is number %d\n", c, c);
        }
    }
    
    fclose(dic);


}

int asignar_num(char readchar)
{
    int modulo = (readchar - 'a') % 26;
    return modulo;
}

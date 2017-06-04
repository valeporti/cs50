/**
 * tt.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * load dictionary and shows how actially tries and "fast hash fuction works"
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
    // load dictionary
    bool loaded = load(dictionary);
    
    // abort if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

}

int asignar_num(char readchar)
{
    int modulo = (readchar - 'a') % 26;
    return modulo;
}



bool load(const char* dictionary)
{
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s!", dictionary);
        return false;
    }
    
    //to append with index the letter to store
    int index = 0;
    char word[LENGTH+1];
    
    //to append with index the key to follow to create tree
    int key[3];
    //int ckey = 0;
    
    int* root;
    int palabra_terminada = 0;
    
    root = malloc()
    
    for (int c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        /**
        *Dentro tiene que estar asignación/creación de true y asignación de palabras a trie
        *Lo que debe de pasar dentro es:
        * 1. Asignar key a primeras 3 letras si existen
        * 2. Guardar palabra en array
        * 3. Guardar palabra en trie con key asignada e ir haciendo una lista dentro de ese key si más de una palabra
        */
        
        //para los tres primeros alojamientos de memoria de 26 bytes, de acuerdo a que la palabra tenga 3 o más de 3 carácteres
        if ((index < 3) && (!isspace(c)))
        {
            //crear memoria para ese número
            word[index] = c;
            key[index] = asignar_num(c);
            index ++;

        }
        //para los tres primeros alojamientos de memoria de 26 bytes, de acuerdo a que la palabra tenga menos de 3 carácteres
        else if ((index < 3) && (isspace(c)))
        {
            //ya se encontró una palabra, es pequeña, 
            //lo que se quiere hacer es colocar el resto del trie y asignar la palabra a ese final de trie
            
            index = 0
        }
        //para cuando se haya terminado de almacenar los 3 alojamientos de memoria y se quiera colocar las palabras con más de 3 characteres
        else if((index > 2) && (c != 10))
        {
            //correr el lector hasta encontrar la palabra completa y colocarla en el final del trie de acuerdo a los 3 dígitos
            
        }
        //significa que ya tenemos la plabra completa
        else
        {
            //colocar palabra en cadena
        }

        
        //if(isalpha(c))
        //{
        //printf("%d\n", c);
        //}
    }
    
    fclose(dic);
    
    return true;
}
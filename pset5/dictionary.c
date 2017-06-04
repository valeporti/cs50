/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
//los agregué
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h> //for strcmp function
//for printing pointers
#include <inttypes.h>

#include "dictionary.h"

trie* root = NULL;
unsigned int palabras_dic = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int wordlen = strlen(word); // length of word
	char low[wordlen+1]; // to store lower case of word
    //convert uppercase in lowercase
    for(int i = 0; word[i]; i++)
		low[i] = tolower(word[i]);
	low[wordlen] = '\0';
	
	int index = 0;
    int key[3]; //to append with index the key to follow to create tree

	//punteros para trie
	trie* pri = NULL;
    trie* seg = NULL;
    //punteros para double linked list
    dll* busca = NULL;
	
	while (index < 3)
	{
	    if (wordlen <= index)
	    {
	        key[index] = key[index-1]; 
	    }
	    else
	    {
	        key[index] = asignar_num(low[index]);
	    }
	    index ++;
	}
	
	if (root->letra[key[0]] == NULL)
    {
        return false;
    }
    else
    {
        //asignar el puntero ya existente en root->letra[key[0]] a pri para que este trabaje con lo siguiente
        pri = root->letra[key[0]];
    }
    if (pri->letra[key[1]] == NULL)
    {
        return false;
    }
    else
    {
        //asignar el puntero ya existente en pri->letra[key[1]] a seg para que este trabaje con lo siguiente
        seg = pri->letra[key[1]];
    }
    //ruta para palabras
    if (seg->dllnum[key[2]] == NULL)
    {
        return false;
    }
    //si sí existe una ese key, significa que es posible la existencia de la palabra
    else
    {
        //buscar en la lista de palabras
        busca = seg->dllnum[key[2]];

        while (busca)
        {
            if (strcmp(busca->palabra, low) == 0)
            {
                return true;
            }
            else
            {
                busca = busca->next;
            }
        }
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * Puntos de mejora: en lugar de pri y seg, se puede hacer una sola ejemplo "trie" y con esa se manejan ambas
 */
bool load(const char* dictionary)
{
    //abrir archivo a leer (diccionario)
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s!", dictionary);
        return false;
    }
    
    //to append with index the letter to store
    int index = 0;
    char word[LENGTH+1];
    //int words = 0;
    
    //to append with index the key to follow to create tree
    int key[3];

    //raíz del trie, de donde empezaremos todo siempre
    //por práctca, sabemos que todos los punteros del trie son NULL
    root = malloc(sizeof(trie));
    root->clave = 0;
    trie* pri = NULL;
    trie* seg = NULL;
    //punteros para double linked list
    dll* motprev = NULL;
    dll* motnouv = NULL;
    
    for (int c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        /**
        *Dentro tiene que estar asignación/creación de true y asignación de palabras a trie
        *Lo que debe de pasar dentro es:
        * 1. Asignar key a primeras 3 letras si existen
        * 2. Guardar palabra en array
        * 3. Guardar palabra en trie con key asignada e ir haciendo una lista dentro de ese key si más de una palabra
        */
        
        //para la lectura de la palabra
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            //aumentar key (pero solo 3 carácteres max e ir aumentndo index para letras en palabra)
            if (index < 3)
            {
                key[index] = asignar_num(c);
            }
            word[index] = c;
            index ++;
        }
        //Se encontró palabra pequeña
        else if (index > 0 && c == '\n')
        {
            //terminar palabra leida
            word[index] = '\0';
            //aumentar conteo de palabras
            palabras_dic ++;

            //asignar último número key al resto de los tres valores de key si es una palabra con 3 letras o menos
            while (index < 3)
            {
                key[index] = key[index - 1];
                index ++;  
            }
            
            //si no existe ruta se crea ruta para palabra -> terminar en ruta deseada
            if (root->letra[key[0]] == NULL)
            {
                pri = malloc(sizeof(trie));
                root->letra[key[0]] = pri;
                pri->clave = key[0];
            }
            else
            {
                //asignar el puntero ya existente en root->letra[key[0]] a pri para que este trabaje con lo siguiente
                pri = root->letra[key[0]];
            }
            if (pri->letra[key[1]] == NULL)
            {
                seg = malloc(sizeof(trie));
                pri->letra[key[1]] = seg;
                seg->clave = key[1];
            }
            else
            {
                //asignar el puntero ya existente en pri->letra[key[1]] a seg para que este trabaje con lo siguiente
                seg = pri->letra[key[1]];
            }
            //ruta para palabras
            //asignar palabra a ruta de trie
            //si no existe clave de palabra en la key, entonces crear
            if (seg->dllnum[key[2]] == NULL)
            {
                motnouv = malloc(sizeof(dll));
                seg->dllnum[key[2]] = motnouv;
                //asignar cada elemento de word a "parola"
                for (int p = 0; word[p] != '\0'; p ++)
                {
                    motnouv->palabra[p] = word[p];
                    motnouv->palabra[p+1] = '\0';
                }
            }
            //si sí existe una clave, significa que hay una palabra, por lo tanto se coloca la nueva palabra en la lista
            else
            {
                //crear nuevo dllist, ajustar los señaladores para que exista previo y next en cada dll
                motprev = seg->dllnum[key[2]];//motprev = señalador a primera palabra (ya existente)
                motnouv = malloc(sizeof(dll));//se coloca memoria par nuevo dll para nueva palabra
                motnouv->next = motprev;//el señalador next del nuevo dll que señale al viejo
                seg->dllnum[key[2]] = motnouv;// y que el señalador del trie señale a este nuevo
                motprev->prev = motnouv;//señalador de la vieja palabra en previo señala al nuevo
                //asignar cada elemento de word a "motnouv"
                for (int p = 0; word[p] != '\0'; p ++)
                {
                    motnouv->palabra[p] = word[p];
                    motnouv->palabra[p+1] = '\0';
                }
            }
            //prepare for next word
            index = 0;
        }
        else
        {
            printf("someting to check (no cases realted isalpha() or end word)");
            return false;
        }
    }
    fclose(dic);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (root != NULL)
    {
        return palabras_dic;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    trie* pri = NULL;
    trie* seg = NULL;
    dll* dll_estudio = NULL;
    dll* dll_movil = NULL;
    
    for (int i = 0; i < 26; i++)
    {
        if ((root->letra[i]) != NULL)
        {
            pri = root->letra[i];
            
            for (int j = 0; j < 26; j++)
            {
                if ((pri->letra[j]) != NULL)
                {
                    seg = pri->letra[j];
                    
                    for (int k = 0; k < 26; k++)
                    {
                        if ((seg->dllnum[k]) != NULL)
                        {
                            dll_estudio = seg->dllnum[k];
                            
                            while ((dll_estudio->next) != NULL)
                            {
                                dll_movil = dll_estudio;
                                dll_estudio = dll_movil->next;
                                
                                free(dll_movil);
                            }
                            free(dll_estudio);
                        }
                    }
                    free(seg);
                }
            }
            free(pri);
        }
    }
    free(root);
    
    return true;
}

/**
 * Funciona como función HASH, regresa un numero del 0 al 15 que sería el número que se necesita para ir haciendo los pasos en el trie
 */
int asignar_num(char readchar)
{
    if(readchar == '\'')
    {
        return 25;
    }
    else if (isalpha(readchar))
    {
        int modulo = (readchar - 'a') % 26;
        
        if (0 <= modulo && modulo <=25)
        {
            return modulo;
        }
        else
        {
            printf("problem with asigantion of key");
            return false;
        }
    }
    else
    {
        printf("there's something wrong, reading other characters than lower case or apostrophe");
        return false;
    }
}
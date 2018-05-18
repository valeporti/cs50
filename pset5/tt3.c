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
#include <cs50.h>
//for printing pointers
#include <inttypes.h>

#include "dictionary.h"

#define DICTIONARY "dictionaries/small"

bool load(const char* dictionary);
int asignar_num(char readchar);

trie* root = NULL;

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
        printf("there's something wrong, reading other characters than lower letter or apostrophe");
        return false;
    }
    
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
    int words = 0;
    
    //to append with index the key to follow to create tree
    int key[3];

    //raíz del trie, de donde empezaremos todo siempre
    //por práctca, sabemos que todos los punteros del trie son NULL
    root = malloc(sizeof(trie));
    root->clave = 0;
    trie* pri = NULL;
    trie* seg = NULL;
    dll* motprev = NULL;
    dll* motnouv = NULL;
    //dll* aver = NULL;
    
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
            words ++;

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
                motprev = seg->dllnum[key[2]];
                motnouv = malloc(sizeof(dll));
                motnouv->next = motprev;
                seg->dllnum[key[2]] = motnouv;
                motprev->prev = motnouv;
                //asignar cada elemento de word a "parola"
                for (int p = 0; word[p] != '\0'; p ++)
                {
                    motnouv->palabra[p] = word[p];
                    motnouv->palabra[p+1] = '\0';
                }

            }
            
            printf("%i - key[%i,%i,%i] - %s\n", words, key[0], key[1], key[2], motnouv->palabra);
            //printf("palabra # %s\n", root->letra[key[0]]->letra[key[1]]->dllnum[key[2]]->palabra);
            
          //  if ((root->letra[0] != NULL) && (root->letra[0]->letra[1] != NULL) && (root->letra[0]->letra[1]->dllnum[1] != NULL))
        //    {
      //          printf("palabra %s letra 1: %i letra 2: %i \n", root->letra[0]->letra[1]->dllnum[1]->palabra, root->letra[0]->clave, root->letra[0]->letra[1]->clave);
    //        }
            
            //prepare for next word
            index = 0;
        }
        else
        {
            printf("someting to check (no cases realted isalpha() or end word)");
            return false;
        }
    }
    printf("palabra 1 %s\n", root->letra[0]->letra[0]->dllnum[0]->palabra);
    printf("palabra 2 en misma cadena %s\n", root->letra[0]->letra[0]->dllnum[0]->next->palabra);
    printf("palabra 3 en misma cadena %s\n", root->letra[0]->letra[0]->dllnum[0]->next->next->palabra);
    printf("next en 3 en misma cadena 0x%" PRIXPTR "\n", (uintptr_t)root->letra[0]->letra[0]->dllnum[0]->next->next->next);
    printf("palabra 4 %s clave1: %i clave2: %i", root->letra[0]->letra[1]->dllnum[1]->palabra, root->letra[0]->clave, root->letra[0]->letra[1]->clave);
    printf("palabra 5 en misma cadena %s\n", root->letra[0]->letra[1]->dllnum[1]->next->palabra);
    printf("next en 5 en misma cadena 0x%" PRIXPTR "\n", (uintptr_t)root->letra[0]->letra[1]->dllnum[1]->next->next);
    printf("palabra 6 %s\n", root->letra[0]->letra[1]->dllnum[2]->palabra);
    printf("palabra 7 %s\n", root->letra[0]->letra[2]->dllnum[2]->palabra);
    printf("palabra 8 en misma cadena %s\n", root->letra[0]->letra[2]->dllnum[2]->next->palabra);
    printf("next en 8 en misma cadena 0x%" PRIXPTR "\n", (uintptr_t)root->letra[0]->letra[2]->dllnum[2]->next->next);
    printf("palabra 9 %s\n", root->letra[0]->letra[25]->dllnum[1]->palabra);
    printf("palabra 10 %s\n", root->letra[0]->letra[1]->dllnum[25]->palabra);
    //root->letra[2] = pri;
    //printf("0x%" PRIXPTR " - ", (uintptr_t)pri);
    //pri->letra[0] = seg;
    //printf("0x%" PRIXPTR " - ", (uintptr_t)seg);
    //seg->dllnum[19] = motnouv;
    //printf("0x%" PRIXPTR " - ", (uintptr_t)motnouv);
    //printf("%s\n", motnouv->palabra);
    
    //for (int i = 0; i < 26; i++)
  //  {
//        if(root->letra[i] != NULL)
        //{
      //      printf("%i 0x%" PRIXPTR "\n", i, (uintptr_t)root->letra[i]);
    //        root->letra[i] = pri;
  //          for (int j = 0; j < 26; j++)
//            {
                //if(pri->letra[j] != NULL)
              //  {
            //        pri->letra[j] = seg;
          //          printf("0x%" PRIXPTR "\n", (uintptr_t)seg);
        //            for (int k = 0; k < 26; k++)
      //              {
    //                    if (seg->dllnum[k] != NULL)
  //                      {
//                            seg->dllnum[k] = motprev;
                            //printf("0x%" PRIXPTR "\n", (uintptr_t)motprev);
                            //printf("%i:root, root->letra[%i]=pri, pri->letra[%i]=seg, seg->dllnum[%i] = mot, mot->palabra = %s - 0x%" PRIXPTR "\n", root->clave, i, j, k, motprev->palabra, (uintptr_t)seg->dllnum[k]);                            
          //              }
        //            }
      //          }
    //        }
  //      }
//
//    }
    
    fclose(dic);
    
    return true;
}
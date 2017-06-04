/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45


/**
 * Typedef Struct for starting search on words, the will here is to decrement the steps of searching (maximum 20 I think).
 */
typedef struct _trie
{
    int clave;
    struct _trie* letra[26];
    struct _dll* dllnum[26];
}
trie;

/**
 * After the trie, I would like to use this trie as linked list (double linked list)
 */
typedef struct _dll
{
    char palabra[LENGTH+1];
    struct _dll* prev;
    struct _dll* next;
}
dll;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Works as a Hash Function, regresa un numero del 0 al 15 que sería el número que se necesita para ir haciendo los pasos en el trie
 */
int asignar_num(char readchar);


#endif // DICTIONARY_H

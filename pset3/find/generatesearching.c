/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // print a warning if there are just 1, 4 or more arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Because even numbers are stored as text, 
    // we have to convert the number text entered for argv[1] into a number (integer)
    int n = atoi(argv[1]);

    // If there are 3 arguments, it means there is a seed (the third argument)
    // with that seed, we can create a "random number" seeded with argv[2]
    // else it would mean that there is no seed, but we're going to "seed it" with a time number
    // since it will always change, the numbers calculated will not be the same
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // the number of random numbers is asked by the variable n
    // We're going to print that quantity of random numbers
    // obtained with an unsigned int (int non negative), drand48 and its seed initialized in the function above
    // multiplied by a number choosen in the upper part (LIMIT)
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
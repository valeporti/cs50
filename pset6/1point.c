/**
 * 1ppint.c
 *
 * Computer Science 50
 * Problem Set 6
 * lookup function
 *
 * es para entender *(*message + *lenght)
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

bool request(int** message, int* length);

int main(void)
{
    int* message = NULL; 
    int lenght = 0; 
    
    bool a_ver = request(&message,&lenght);
    if (a_ver)
    {
        printf("true");
    }
    
}

bool request(int** message, int* length)
{
    int control = 0;
    *length = 1;
    int array[] = {0,1,2,3,4};
    *message = &array[0];
    control = *(*message + *length);
    if (control == 3)
    {
        
        return true;
    }
    else
    {
        return false;
    }
}
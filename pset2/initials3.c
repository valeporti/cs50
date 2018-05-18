#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    printf("Please, write your Name - ");
    string name = GetString();
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        
        printf("%c", toupper(name[i]));
    }
    printf("\n");
}
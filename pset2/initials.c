#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string name = GetString();
    int space = 32;
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (i == 0 && name[i] != space)
        {
            printf("%c", toupper(name[i]));
        }
        else if (name[i] == space)
        {
            printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
}
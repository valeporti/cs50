#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//main will call for arguments 
int main(int argc, string argv[])
{
    int sum = 0;
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if(isalpha(argv[1][i]))
            {
            }
            else
            {
                sum = sum + 1;
            }
        }
    }
    if (sum == 0 && argc == 2)
    {
        string key = argv[1];
        char subsletter = 'a';
        string message = GetString();
        
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            int m = (strlen(key));
            printf("lenght message: %i -", n);
            printf("lenght key: %i -", m);
            int letterkey = (i+1) % m ;
            printf("(i+1)/m:%i - ", letterkey);
            char startptupp = 'A';
            char startkupp = 'A';
            char startptlow = 'a';
            char startklow = 'a';
            
            
            if (isupper(message[i]))
            {
                startptupp = message[i] - 'A';
            }
            else if (isupper(key[letterkey]))
            {
                startkupp = key[letterkey] - 'A';
            }
            else if (islower(message[i]))
            {
                startptlow = message[i] - 'a';
            }
            else if (islower(key[letterkey]))
            {
                startklow = key[letterkey] - 'a';
            }
            else
            {
                printf("%c\n", message[i]);
            }
            printf("%c", startptupp);
            printf("%c", startkupp);
            printf("%c", startptlow);
            printf("%c", startklow);
            
            int modulo = ((startptupp + startptlow) + (startkupp + startklow)) % 26;
            printf(" modulo: %i - ",  modulo);
            if (isupper(message[i]))
            {
                subsletter = ('A') + modulo;
            }
            else if (islower(message[i]))
            {
                subsletter = ('a') + modulo;
            }
            printf("print: %c\n", subsletter);
        }
    }
    else
    {
        printf("Just Letters!! : ");
        return 1;
    }
}
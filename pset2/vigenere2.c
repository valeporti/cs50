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
            for (int j = i, m = strlen(key); j < m, j++)
            {
                int siserepite = (i % j)
                if (isalpha(message[i]) && isupper(message[i])
                {
                    int startpt = message[i] - 'A';
                    int startk = key[j] - 'A'
                    int modulo = (startpt + startk) % 26;
                    subsletter = ('A' - 1) + modulo;
                    printf("%c", subsletter);
                    
                }
                if (isalpha(message[i]) && islower(message[i])
                {
                    
                }
                else
                {
                    printf("%c", message[i]);
                }
            }
        }
    }
    else
    {
        printf("Just Letters!! : ");
        return 1;
    }
}
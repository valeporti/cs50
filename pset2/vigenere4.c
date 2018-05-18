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
        string message = GetString();
        int k = 0;
        
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            //para ver qué numero de letra de la key se pone
            int m = (strlen(key));
            printf("lenght message: %i -", n);
            printf("lenght key: %i -", m);
            
            //hay que ver si hay espacio o es letra 
            //pues no se debe desperdiciar una letra en un espacio 
            if (isalpha(message[i]))
            {
                int letterkey = (k) % m ;
                printf("# letra key : %i- ", letterkey);
                k ++;
                
                //estudiatremos primero el key 
                int lugark = key[letterkey];
                if (islower(key[letterkey]))
                {
                    lugark = lugark - 'a';
                }
                else if (isupper(key[letterkey]))
                {
                    lugark = lugark - 'A';
                }
                else
                {
                    printf("error para el estudio de key\n");
                }
                printf("se sumará: %i - ", lugark);
                
                //estudiaremos las letras del mensaje a cifrar
                //y haremos el cifrado
                int lugarm = message[i];
                printf("del '0' + %i - ", lugarm);
                char subsletter = 'a';
                if (isupper(message[i]))
                {
                    lugarm = lugarm - 'A';
                    subsletter = ((lugark + lugarm) % 26) + 'A';
                    printf("letra sustituida: %c\n", subsletter);
                }
                else
                {
                    lugarm = lugarm - 'a';
                    subsletter = ((lugark + lugarm) % 26) + 'a';
                    printf("letra sustituida: %c\n", subsletter);
                }
                
            }
            else
            {
                printf("no es letra: %c\n", message[i]);
            }
        }
    }
    else
    {
        printf("Just Letters!! : ");
        return 1;
    }
}
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//main will call for arguments 
int main(int argc, string argv[])
{
    //to verify if there's just one argument (the name of the program)
    //or more than two arguments (we only ask for one input)
    if (argc == 1 || argc > 2)
    {
        //return a value of 1 implies error
        return 1;
    }
    
    //convert the string input to a integer
    int k = atoi(argv[1]);
    printf("%i\n", k);
    
    //ask the user for plaintext to cipher
    printf("please, write message to cipher: ");
    string message = GetString();
    printf("%s\n", message);
                
    
    //cipher the plaintext
    for (int i = 0, n = strlen(message); i < n ; i++)
    {
       
    
        if isalpha(message[i])
        {

            //para saber si se encuentra dentro del intervalo de letras
            //o podría imprimir algo que no es una letra
            char subsletter = 'a';
            
            if (isupper(message[i]))
            {
                int modulo = (message[i] - 'A' + k) % 26;
                printf("%i - ", modulo);
                subsletter = 'A' + modulo;
            }
            else if (islower(message[i]))
            {
                int modulo = (message[i] - 'a' + k) % 26;
                printf("%i - ", modulo);
                subsletter = 'a' + modulo;
            }
            printf("%c\n", subsletter);
        }
        else
        {
            printf("%c\n - ", message[i]);
        }
        
    }
    return 0;
}
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//main will call for arguments 
int main(int argc, string argv[])
{
    printf("%s", argv[1]);
 
    int sum = 0;
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
    
    if (sum == 0 && argc == 2)
    {
        printf("aqui");
    }
    else
    {
        printf("Asign a valid String!! : ");
        return 1;
    }
    
   

    //if (argc == 2 && isalpha(argv[1]))
    //{
        //printf("hola");
    //}
    //else
    //{
       // printf("no salio");
    //}
}
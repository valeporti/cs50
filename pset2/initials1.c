#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main (void)
{
    printf("Please, write your Name - ");
    string name = GetString();
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] >= 'a' && name[i] <= 'z')
        {
            printf("%c", name[i] - ('a' - 'A'));
        }
        else
        {
            printf("%c", name[i]);
        }
    }
    printf("\n");
}
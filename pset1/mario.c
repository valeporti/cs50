#include <stdio.h>
#include <cs50.h>

int main(void)
{
   int x;
   do
   {
       printf("Height (type positive number between 1 and 23 inclusive): ");
       x = GetInt();
   }
   while (x < 0 || x > 23);
      
    for (int  i = 0; i < x; i++)
    {
        int n = x - i;
        for (int k = n - 1; k > 0 ; k--)
        {
            printf(" ");
        }
        for (int l = i + 2; l > 0; l--)
        {
            printf("#");
        }
        printf("\n");
    }
}
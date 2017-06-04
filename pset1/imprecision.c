#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float x;
    
    do 
    {
        printf("Write an amount on dollars to greedy: ");
        x = GetFloat();
    }
    while (x < 0);

    float y;
    int z;
    
    y = 100 * x;
    float roundf(float y);
    printf("%f\n",y);
    z = (int) round(y);
    printf("%i\n",z);

}
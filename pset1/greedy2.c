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
  
    int quarter;
    float Q;
    Q = y/25;
    quarter = (int) round(Q);
    printf("%i\n",quarter);
    float D;
    float di;
    int dime;
    D = (y % 25.00);
    di = D/10;
    printf("%f\n",D);
    dime = (int) round(D);
    printf("%i\n", dime);
    
    
}
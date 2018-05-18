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
    
    int quarter = z;
    int qcounter = 0;
    for (int i = 0; quarter >= 25 ; i++)
    {
        quarter = quarter - i*25;
        qcounter = qcounter + 1 ;
    }
    if (qcounter == 0)
    {
        
        printf("Quarters: 0\n");
    }
    else
    {
        printf("Quarters: %i\n", qcounter - 1);
    }
    printf("remainder %i\n", quarter);
    
    int dime = quarter;
    int dcounter = 0;
    for (int i = 0; dime >= 10 ; i++)
    {
        dime = quarter - i*10;
        dcounter = dcounter + 1;
    }
    if (dcounter == 0)
    {
         printf("Dimes: %i\n", dime);
    }
    else
    {
        printf("Dimes: %i\n", dcounter - 1);
    }
    printf("remiander %i\n", dime);
    
    int nickel = dime;
    int ncounter = 0;
    for (int i = 0; nickel >= 5; i++)
    {
        nickel = nickel - i*5;
        ncounter = ncounter + 1;
    }
    if (ncounter == 0)
    {
        printf("Nickels: 0\n");
    }
    else
    {
    printf("Nickels: %i\n", ncounter - 1);
    }
    printf("remainder %i\n", nickel);
    
    int penny = nickel;
    int pcounter = 0;
    for (int i = 0; penny >= 1; i++)
    {
        penny = penny - i;
        pcounter = pcounter + 1;
    }
    if (pcounter == 0)
    {
        printf("Pennys: %i\n", penny);
    }
    else
    {
        printf("Pennys: %i\n", pcounter);
    }
    printf("remainder %i\n", penny);
}
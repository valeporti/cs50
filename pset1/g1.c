# include <stdio.h>
# include <math.h>
# include <cs50.h>

int main (void)
{
    /*ask user a number"*/
    float x;
    do
    {
        printf("Amount on dollars please: \n");
        x = GetFloat();
    }
    while (x <= 0);
    
    float y = x * 100;
    int z = (int) round(y);
    printf("con round %i\n",z);
    
    int quarters = z;
    int counterq = 0;
    for (int i = 1 ; quarters >= 25 ; i++ )
    {
        quarters = z - i * 25;
        counterq = i;
    }
    printf("remainder %i\n", quarters);
    printf("quarters %i\n", counterq);
    
    int counterd = 0;
    int dimes = quarters;
    for (int i = 1 ; dimes >= 10 ; i++ )
    {
        dimes = quarters - i * 10;
        counterd = i;
    }
    printf("dimes remainder %i\n", dimes);
    printf("dimes: %i\n", counterd);    
    
    int countern = 0;
    int nickels = dimes;
    for (int i = 1 ; nickels >= 5 ; i++)
    {
        nickels = dimes - i * 5;
        countern = i;
    }
    printf("nickels remainder %i\n", nickels);
    printf("nickels: %i\n", countern);
    
    int counterp = 0;
    int pennys = nickels;
    for (int i = 1 ; pennys >= 1 ; i++)
    {
        pennys = nickels - i;
        counterp = i;
    }
    printf("remainder pennys %i\n", pennys);
    printf("pennys: %i\n", counterp);
    
    int coins = 0;
    coins = counterp + countern + counterd + counterq;
    printf("total of coins : %i\n", coins);
}
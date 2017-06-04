# include <stdio.h>
# include <math.h>
# include <cs50.h>

int main (void)
{
    /*ask user a number"*/
    float x;
    do
    {
        printf("Amount on dollars please: ");
        x = GetFloat();
    }
    while (x <= 0);
    
    /*convert number to an integer to work easyly and accurately with it*/
    float y = x * 100;
    int z = (int) round(y);
    
    /*way of counting*/
    /*worked with "for" counting the number of coins until reaching the maximum for each*/
    int quarters = z;
    int counterq = 0;
    for (int i = 1 ; quarters >= 25 ; i++ )
    {
        quarters = z - i * 25;
        counterq = i;
    }
    
    int counterd = 0;
    int dimes = quarters;
    for (int i = 1 ; dimes >= 10 ; i++ )
    {
        dimes = quarters - i * 10;
        counterd = i;
    }
    
    int countern = 0;
    int nickels = dimes;
    for (int i = 1 ; nickels >= 5 ; i++)
    {
        nickels = dimes - i * 5;
        countern = i;
    }
    
    int counterp = 0;
    int pennys = nickels;
    for (int i = 1 ; pennys >= 1 ; i++)
    {
        pennys = nickels - i;
        counterp = i;
    }

    /*print the answer of the sum of coins*/
    int coins = 0;
    coins = counterp + countern + counterd + counterq;
    printf("%i\n", coins);
}
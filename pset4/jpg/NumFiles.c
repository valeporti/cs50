/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "help.h"

int main(int argc, char* argv[])
{
    // TODO
    // First, I would like to know how many files are there in (should be 50)
    //
    //PseudoCode
    //1. Open File
    //2. Search for beginnings of files
    //3. Count beginnings
    //
    //We know JPEGs are written in 512 bytes blocks
    //We know first three bytes are: 0xff 0xd8 0xff
    //We know the fourth byte should start with 0xe_ , so the first four bits of the fourth bytes are 1110
    //That means that we can read the first 4 bytes and we'll have: 1111 1111 1101 1000 1111 1111 1110 ____
    //Here we got just two combinations for the last byte, 0000 or 0001
    
    // ensure proper usage
    if (argc != 1)
    {
        printf("Usage: ./NumFiles (no command line arguments)\n");
        return 1;
    }
    
    //File to open
    //char infile = "card.raw";
    
    // open file to read, verify if there's no problem
    FILE* toread = fopen("card.raw", "r");
    if (toread == NULL)
    {
        printf("Could not open 'card.raw'.\n");
        return 2;
    }
    
    int countfiles = 0;
    
    //512 bytes variable
    //BYTE block[512];
    //fread(&block, sizeof(block), 1, toread);
    
    //colocar enel principio del archivo el cursor
    fseek(toread, 0, SEEK_SET);
    //buscar un primer match para partir de ahí el conteo de cada 512 bytes
    BYTE Oblock[512];
    fread(&Oblock, sizeof(Oblock), 1, toread);
    
    int found = 0;
    int cuantos_antesde = 0;
    //BYTE UNone = 0;
    //BYTE UNtwo = 0;
    //BYTE UNthr = 0;
    //BYTE UNfou = 0;
    
    do 
    {
        //UNone = Oblock[0];
        //UNtwo = Oblock[1];
        //UNthr = Oblock[2];
        //UNfou = Oblock[3];
        
        if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)))
        {
            found = found + 1;
        }
        else
        {
            fread(&Oblock, sizeof(Oblock), 1, toread);
            cuantos_antesde = cuantos_antesde + 1;
        }
        
        //printf("%hhu, %hhu, %hhu, %hhu", UNone, UNtwo, UNthr, UNfou);
    }
    while (found == 0);

    int ver_fread = 0;
    
    do
    {
        
        if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)))
        {
            countfiles = countfiles + 1;
        }
        //int l = (fread(&block, sizeof(block), 1, toread));
        //int m = (fread(&block, sizeof(block), 2, toread));
        //int n = (fread(&block, sizeof(block), 3, toread));
        //printf("l %i", l);
        ver_fread = fread(&Oblock, sizeof(Oblock), 1, toread);
        //printf("fr %i - ", ver_fread);
    }
    while (ver_fread == 1);
    
    printf("# %i\n", countfiles);
    printf("# %i\n", cuantos_antesde);
    
    fclose(toread);

}

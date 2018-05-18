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
#include <stdint.h>
#include <cs50.h>


typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // TODO
    //
    //Search for begginings of files, create different files separating the different jpg images
    //1. Open File to search in
    //2. Search the first begining
    //3. Start copiyng that infromation to the outfile until another begining of file is reached (files are one after another)
    //4. Close each file before starting with the other, the count is fromm 000.jpg
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
    
    // open file to read, verify if there's no problem
    FILE* toread = fopen("card.raw", "r");
    if (toread == NULL)
    {
        printf("Could not open 'card.raw'.\n");
        return 2;
    }
    
    //buscar un primer match para partir de ahí el conteo de cada 512 bytes
    BYTE Oblock[512];
    fread(&Oblock, sizeof(Oblock), 1, toread);
    
    int found = 0;
    
    do 
    {
        if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)))
        {
            found = found + 1;
        }
        else
        {
            fread(&Oblock, sizeof(Oblock), 1, toread);
        }
    }
    while (found == 0);

    //archivo terminado lo marcará la función fread, y se considera terminado con 1
    int archivoterminado = 0;
    //conteo dearchivos
    int countfiles = 0;
    
    FILE* newjpg = NULL;
    
    while (archivoterminado == 0)
    {
        //Open file
        //name of file
        char title[8];
        sprintf(title, "%03d.jpg", countfiles);
        // open output file
        newjpg = fopen(title, "w");
        if (newjpg == NULL)
        {
            fclose(toread);
            fprintf(stderr, "Could not create %s\n", title);
            return 3;
        }
        
        int notnewstart = 0;
        
        if (countfiles == 49)
        {
            notnewstart = 1;
            archivoterminado = 1;
        }
        
        // write on it        
        while(notnewstart == 0 && archivoterminado == 0)
        {
            fwrite(&Oblock, sizeof(Oblock), 1, newjpg);
        
        // search for next block
            if((fread(&Oblock, sizeof(Oblock), 1, toread)) < 1)
            {
                archivoterminado = 1;
            }

        // verify if it's ended, if it isn't continue writing on the opened file, else, close the old one and open another one            
            if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)) && archivoterminado == 0)
            {
                notnewstart = 1;
                countfiles = countfiles + 1;
            }
        }
         if (newjpg != NULL)
        {
            fclose(newjpg);
        }
    }
    //if (newjpg != NULL)
    //{
    //    fclose(newjpg);
    //}
    if (toread != NULL)
    {
        fclose(toread);
    }
    
    return 0;
}

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
        printf("Usage: ./recover (no command line arguments)\n");
        return 1;
    }
    
    // open file to read, verify if there's no problem
    FILE* toread = fopen("card.raw", "r");
    if (toread == NULL)
    {
        printf("Could not open 'card.raw'.\n");
        return 2;
    }
    
    //variables para la lectua de archivo salida
    int contador_archivo = 0;
    int marcador_inicio = 0;
    int final_archivo = 0;
    int primer_archivo = 0;

    while (final_archivo == 0)
    {
        //variable temporal que almacena información
        BYTE Oblock[512];
        
        char title[8];
        sprintf(title, "%03d.jpg", contador_archivo);
        // open output file
        FILE* archivo_nuevo = fopen(title, "w");
        if (archivo_nuevo == NULL)
        {
            fclose(toread);
            fprintf(stderr, "Could not create %s\n", title);
            return 3;
        }
        
        if (contador_archivo != 0)
        {
            primer_archivo = 1;
        }
        
        marcador_inicio = 0;
        while (marcador_inicio == 0)
        {
            if (primer_archivo == 1)
            {
                fwrite(&Oblock, sizeof(Oblock), 1, archivo_nuevo);
            }
            
            if (fread(&Oblock, sizeof(Oblock), 1, toread) == 0)
            {
                final_archivo = 1;
            }
            else if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)))
            {
                if (primer_archivo == 1)
                {
                    marcador_inicio = 1;
                    contador_archivo = contador_archivo + 1;
                }
            }
            else
            {
                marcador_inicio = 0;
            }
        }
        if (primer_archivo == 1)
        {
            fclose(archivo_nuevo);
        }
    }
    fclose(toread);

    return 0;
}

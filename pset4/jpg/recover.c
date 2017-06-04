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
    
    BYTE Oblock[512];
    
    int contador = 0;
    FILE* nueva_imagen = NULL;
    
    while ((fread(&Oblock, sizeof(Oblock), 1, toread)) == 1)
    {
        if (((Oblock[0] == 0xff) && (Oblock[1] == 0xd8) && (Oblock[2] == 0xff)) && ((Oblock[3] == 0xe0) || (Oblock[3] == 0xe1)))
        {
            if (nueva_imagen != NULL)
            {
                fclose(nueva_imagen);
            }
            char title[8];
            sprintf(title, "%03d.jpg", contador);
        
            nueva_imagen = fopen(title, "w");
            if (nueva_imagen == NULL)
            {
                fclose(toread);
                fprintf(stderr, "Could not create %s\n", title);
                return 3;
            }
            
            contador ++;
        }
        if (nueva_imagen != NULL)
        {
            fwrite(&Oblock, sizeof(Oblock), 1, nueva_imagen);
        }
    }
    if (nueva_imagen != NULL)
    {
        fclose(nueva_imagen);
    }
    fclose(toread);
    
    return 0;
    
    //al parecer, uno de los errores que ometía era que dejaba memoria sin cerrar
    //seguramente tenga que ver los fclose de al final
    // fue sabio usar el FILE* = NULL
    //ANTES
   // ==14410== HEAP SUMMARY:
//==14410==     in use at exit: 1,136 bytes in 2 blocks
//==14410==   total heap usage: 51 allocs, 49 frees, 28,968 bytes allocated
//==14410== 
//==14410== LEAK SUMMARY:
//==14410==    definitely lost: 0 bytes in 0 blocks
//==14410==    indirectly lost: 0 bytes in 0 blocks
//==14410==      possibly lost: 0 bytes in 0 blocks
//==14410==    still reachable: 1,136 bytes in 2 blocks
//==14410==         suppressed: 0 bytes in 0 blocks
//==14410== Rerun with --leak-check=full to see details of leaked memory

//DESPUES
//==1373== HEAP SUMMARY:
//==1373==     in use at exit: 0 bytes in 0 blocks
//==1373==   total heap usage: 51 allocs, 51 frees, 28,968 bytes allocated
//==1373== 
//==1373== All heap blocks were freed -- no leaks are possible

//Lo que significa que si había o hay 51 allocs que liberar y faltaban dos, no se si sería cuestión de verificar los fclose

//en el recover 4, lo que se entiende es que lo que me faltaba era cerrar el último documento y escribir la última parte del documento
//por la forma en que están acomodadas las cosas
}

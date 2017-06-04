/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    // remember changing size number
    int n = atoi(argv[1]);
    
    if ((n < 1) || (n > 101))
    {
        printf("n must be [1, 100]");
        return 4;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, big_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    big_bf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, big_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    big_bi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

//See by how much and how we're going to increase quantities to modify in both headers
    //biHeight = ffff ffff - (ffff ffff - ffff fffx)*n OR 4294967295 - (4294967295 - 42949672xx)*n
    //biWidth = x*n
    //bfSize = bf.bfSize - bi.biSizeImage + newbiSizeImage;
    //biSizeImage = (newWidth * sizeof(RGBTRIPLE) + res_padding) * abs(newbiHeight);
    big_bi.biHeight = bi.biHeight * n;
    big_bi.biWidth = bi.biWidth * n;
    //we have to determine the padding before, both, new and old one because we use it in the image size
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int big_padding = (4 - (big_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    big_bi.biSizeImage = (big_bi.biWidth * sizeof(RGBTRIPLE) + big_padding) * abs(big_bi.biHeight);
    big_bf.bfSize = bf.bfOffBits + big_bi.biSizeImage;
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&big_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&big_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    //int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
         for (int l = 0; l < n; l++)
        {
            if (l != 0)
            {
                fseek(inptr, - bi.biWidth * sizeof(RGBTRIPLE) - padding, SEEK_CUR);
            }
                
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < big_padding; k++)
        {
            fputc(0x00, outptr);
        }
        
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

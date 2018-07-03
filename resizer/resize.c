/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <math.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize size infile outfile\n");
        return 1;
    }

    //get float size
float f=atof(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    //created new bitmapfileheader
    BITMAPFILEHEADER newbf = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //create new bitmapinfoheader
    BITMAPINFOHEADER newbi = bi;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    

    //new header info for the resulting new size
     newbi.biWidth=(bi.biWidth*f);
     newbi.biHeight=(bi.biHeight*f);
    //determining new padding
    int newpadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE))%4)%4;
    //determining new bisizeimage
    //determining new bfsize
        newbi.biSizeImage = (newbi.biWidth * sizeof(RGBTRIPLE) + newpadding) * abs(newbi.biHeight);
        newbf.bfSize = newbi.biSizeImage + 54;


    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);


//downsizing
//in order to downsize we need to create two variables for the horizontal and vertical scaling. This variables contains the value which allow us to decide if the pixel should be written or not
    if (f < 1.0) {
        float width_scale = (float) bi.biWidth / (float) newbi.biWidth;
        float height_scale = (float) abs(bi.biHeight) / (float) abs(newbi.biHeight);
        
        // counter for outfile's scanlines
        float out_scanlines = 0.0;
        
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // pick or reject current scanline
            if ((out_scanlines < biHeight) && (i >= out_scanlines || i == biHeight-1))
            {
                // counter for pixels of in outfile's scanline
                float out_pixels = 0.0;
                
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
                    // pick or reject current pixel
                    if ((out_pixels < bi.biWidth) && (j >= out_pixels || j == bi.biWidth-1))
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        out_pixels += width_scale;
                    }
                }
        
                // skip over infile padding, if any
                fseek(inptr, padding, SEEK_CUR);
        
                // add resized padding to outfile
                for (int k = 0; k < newpadding; k++)
                {
                    fputc(0x00, outptr);
                }
                
                out_scanlines += height_scale;
            } else {
                // skip current scanline
                fseek(inptr, (sizeof(RGBTRIPLE) * bi.biWidth) + padding, SEEK_CUR);
            }
        }
    fclose(inptr);
    fclose(outptr);
        return 0;
    }

//increasing size
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int factornumber=0;factornumber<f;factornumber++){
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int w=0; w<f; w++){
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
            // then add it back (to demonstrate how)
             for (int k = 0; k < newpadding; k++)
              {
               fputc(0x00, outptr);
             }
            
          fseek(inptr,-(padding+3*bi.biWidth),SEEK_CUR);
        }
          fseek(inptr,(padding+3*bi.biWidth),SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

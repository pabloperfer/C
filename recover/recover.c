//program that recovers JPEGs from a forensic image


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover sourceimg \n");
        return 1;
    }

    // remember filenames
    char* sourceimg = argv[1];

    // open input file 
    FILE* imgptr = fopen(sourceimg, "r");
    if (imgptr == NULL) {
        fprintf (stderr, "Could not open  %s. \n",sourceimg); 
        return 2;
    } 

unsigned char buffer[512];
int imgcounter=0;
FILE* file=NULL;
char filename[sizeof "100.jpg"];
    
fread(buffer, 512 , 1, imgptr);
while (fread(buffer, 512, 1, imgptr) == 1){
    if ((buffer[0]==0xff) && (buffer[1]==0xd8) && (buffer[2]==0xff) &&buffer[3]>= 0xe0)
        {
        if (file!=NULL){
                    fclose(file);
                  }
         sprintf(filename, "%03d.jpg", imgcounter);
         file=fopen(filename,"w");
         imgcounter++; 
        }
   if(file!=NULL){           
       //if no jpg headers and file exist we write the content 
           fwrite(buffer, 512 , 1, file);
           }
    }
 fclose(file);
 fclose(imgptr);
  return 0;
}

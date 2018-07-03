/* cracks hash DSE algorithm
 *  
 *  By taking the lowest 7 bits of each of the first eight characters of the key, a 56-bit key is obtained.
 *  This 56-bit key is used to encrypt  repeatedly a constant  string  (usually a string consisting of all zeros).  
 *  The returned value points to the encrypted password, a series of 13 printable ASCII characters (the first two characters represent the salt itself).  
 *  salt is the 2 first characters of a hashed pasword
 *  */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
char salt[3];
char key[5];
int c;

char *crypt(const char *key,const  char *salt);

int main (int argc,string argv[]) {
        if (argc!=2) {
                    printf ("Usage: ./crack hash\n");
                    return 1;
                     }
        else if (argv[1] != NULL)
                    {
/*hallamos el salt a partir de la key hashed*/
         strncpy(salt, argv[1], 2); //put the 2 character salt into the salt variable
         printf("the salt is: %s\n", salt);
/*como sabemos que la pass no tiene mas de 4 caracteres, comparamos todos 
// los hash generados con el salt para las combinaciones alfanumericas hasta 4 bytes*/
//primero un for para iterar los 5 bytes, 4 letras mas el nulo
        for (int i=0; i<5; i++) {
         //anidado un for que saque las combinaciones por cada byte, para un byte todo desde a-Z, 
         //para el siguiente dos veces eso.
         if (i==0){
          for (char x=65;x<=122;x++) {
               key[i]=x;
               key[1]='\0';
               string pass=crypt(key,salt);
               c=strcmp( pass, argv[1]);
               if (c==0){
               printf ("password is %s\n",key);
               return 0;
                      }
                 }
            }
         if (i==1){
               for (char x0=65;x0<=122;x0++){
                     key[0]=x0;
                     for (char x1=65;x1<=122;x1++){
                         key[1]=x1;
                         key[2]='\0';
                         string pass=crypt( key, salt);
                         c=strcmp(pass, argv[1]);
                         if (c==0){
                           printf ("password is %s\n",key);
                           return 0;
                                  }
                            }
                          } 
                       }
                    
         if (i==2){
              for (char x0=65;x0<=122;x0++){
                     key[0]=x0;
                     for (char x1=65;x1<=122;x1++){
                        key[1]=x1;
                         for (char x2=65;x2<=122;x2++) {
                            key[2]=x2;
                            key[3]='\0';
                            string pass=crypt( key, salt);
                            c=strcmp( pass,argv[1]);
                            if (c==0){
                                 printf ("password is %s\n",key);
                                 return 0;
                                     } 
                                }
                        }
                    }
                  }
          if (i==3) {
              for (char x0=65;x0<=122;x0++){
                key[0]=x0;
                  for (char x1=65;x1<=122;x1++){
                    key[1]=x1;
                      for (char x2=65;x2<=122;x2++) {
                        key[2]=x2;
                        for (char x3=65;x3<=122;x3++) {
                            key[3]=x3;
                            key[4]='\0';
                            string pass=crypt( key, salt);
                            c=strcmp(pass,argv[1]);
                            if (c==0){
                                 printf ("password is %s\n",key);
                                 return 0;
                                      } 
                                    }
                                               }
                                           } 
                                       }
                      }
        //char *crypt(const char *key, const char *salt);
                }
            }
}

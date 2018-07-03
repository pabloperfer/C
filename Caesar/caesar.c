
/*Caesar’s algorithm encrypts messages by "rotating" each letter by "k" positions. 
 *
  If "p" is some plaintext, pi is the ith character in p, and k is a secret key (non-negative integer), 
  then each letter, ci, in the ciphertext, c, is computed as
 
  ci=(pi+k)mod26
  ci=(pi+k)mod26
 
  wherein mod26 here means "remainder when dividing by 26." 
  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main (int argc,string argv[]) {
         if (argc!=2) {
           printf ("Usage: ./caesar positiveinteger \n");
           return 1;
                      }
         else if (argv[1] != NULL) {
          //make sure it's positive and bigger than 0
          int k = atoi(argv[1]);
          if (k < 0){
               printf ("Usage : integer has to be bigger than 0 " );
               return 1 ;
               }
          //if k is greater than 26, alphabetical characters in your program’s input should remain alphabetical characters in your program’s output.
          else if (k > 26){
              int x=k;
              k = x%26;
                }
    
          //once i have the k value i prompt the user for plaintext
          string s = get_string("plaintext: ");
           if (s == NULL) {
                    return 1;
                    }
           //now we need to apply the caesar logic in order to provide the ciphered text
           printf("ciphertext: ");
           for (int i=0,j=strlen(s); i<j;i++){
                if (s[i] <=90){
                    int ascii=s[i]+k;
                    if (ascii >90){
                        int sustrato=26-k;
                        ascii = ascii-sustrato-k;
                        s[i]=ascii;
                        printf("%c", s[i]);
                    }
                    else {
                        printf("%c", s[i]+k);

                    }
                }
                if (s[i]>=97){
                    int ascii=s[i]+k;
                    if (ascii>122){
                        int sustrato=26-k;
                        ascii = ascii-sustrato-k;
                        s[i]=ascii;
                        printf("%c", s[i]);
                           }
                else {
                        printf("%c", s[i]+k);
                    
                        }
                 }
         }
           printf ("\n");
    }
}

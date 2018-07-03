#include <stdio.h>
#include <cs50.h>
/*credit number Implement a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.*/
int main (void){
    int digit=0;
    bool valid = false;
    long long num;
    long long everyother;
    long long secondlast;
    int  acum=0;
    int acum2=0;
    long long num2;
    long long num3;
    string cardtype="test";
      do{
             printf("Number:");
                num = get_long_long(); 
                  }while(num==0 | num<0);
        num2=num;
        num3=num;
        /* multiply every other digit starting from the second til the last digit */
        /*last digit number%10 */
        /*378282246310005 should result 25*/
 
              while (digit<9) {
                    everyother= num / 10;
                    secondlast= everyother % 10;
                    if (secondlast>=5) {
                        secondlast=secondlast*2;
                        secondlast = secondlast%10+secondlast/10;
                        acum=secondlast +acum;
                    }
                    else{
                    acum= secondlast * 2 + acum;
                    }
                    num=num/100;
                    digit++;
             }                        
            digit=0;
         while (digit<9) {
                 secondlast= num2%10;
                 acum2=secondlast+acum2;
                 num2=num2/100;
                 digit++;
              }
            int sum = acum+acum2;
            if (sum%10==0){
          valid=true;
          
            }
            else{
                printf ("INVALID\n");
          }
        if (valid==true){
            if (num3/10000000000000<10){
                cardtype="VISA";}
             else if(num3/100000000000000<10){
                cardtype="AMEX"; }
             else if (num3/10000000000000000<10){
                if(num3/100000000000000>50) {
                cardtype="MASTERCARD";}
                else{
                cardtype="VISA";}
                                   }
            printf ("%s\n",cardtype); 
                  }
              
       }


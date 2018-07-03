/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include<stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0) {
     //   binary search within a loop
       return false;
              }
     else {
          int lowest=0;
          int highest=n-1;
          int mid = lowest + (highest-lowest)/2;
          while (lowest <= highest) {
           if (values[mid]<value){
                lowest=mid+1;
                     }
           else if (values[mid]==value) {
                     return true; 
                    }
           else{
            highest=mid-1;
                }
            mid = (lowest+highest)/2;
              }
         return false;
          }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n){
    //counting sort
    int preordered[65536]= {0};

    // i fill the preordered array with the number of ocurrence of each number in the array in each correspondent index 
    for (int i=0; i<n; i++) {
                preordered[values[i]]++;
    }
   
   int orderedindex=0;
      for (int j=0;j<65536;j++){ 
             if (preordered[j]>0){
                for (int a=0;a<preordered[j];a++){
                values[orderedindex]=j;  
                orderedindex++;
                }}
            } 
      } 

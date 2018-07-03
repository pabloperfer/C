/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated declared as a constant value
#define LIMIT 65536


int main(int argc, string argv[])
{
    // if the number of arguments is different that 2 or 3 returns 1 and prints the correct usage 
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // it declares the variable n which takes the first argument, this is the number of numbers generated and ensures it's and converts to int just in case
    int n = atoi(argv[1]);

    // if the number of arguments is 3 it means that a seed is provided so it invokes the randoe function passing the int value of the second argument, if not using the seed it uses the time by default as it's always different
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // for n times it invokes the function drand48 which requires srand being invoked first as it's an initialization function, it multiplies the resulting randome value by limit value
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}

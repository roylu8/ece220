#include <stdlib.h>
#include <stdio.h>

// Errors in is_prime include in the first if statement,
// checked for the wrong value and returned the wrong value,
// which allowed 2 to be printed even though it is not semiprime.
// The return values were flipped so the program would 
// return the opposite value. 
// In print_semiprimes, second for loop shouldn't iterate
// to j = i or else every value between a and b will be printed.
// k = i%j >> k = i/j or else non semiprime values will be printed.
// Implement repeat checker so no repeated values are printed.

// partners: briolat2, kaylanw4


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 2) {return 1;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <= b; i++) { //for each item in interval
        //check if semiprime
        int repeat = 0;
        for (j = 2; j < i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        if (repeat == 0){
                            printf("%d ", i);
                            repeat = 1;
                        }
                    
                        
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}

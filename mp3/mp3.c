#include <iostream>

//This program prints the nth row of a pascal's triangle
//partners: briolat2, kaylanw4

int main() {
    int row;
    unsigned long pascal;

    printf("Enter a row index: ");							//ask for which row to print
    scanf("%d", &row);

    for(int i=0; i<=row; i++){
        pascal=1;											//initialize coefficient
        for(int k=1; k<=i; k++)
            pascal=(pascal*(unsigned long)((row+1-k))/k);  	//apply formula
        printf("%lu ", pascal);								//print to console
    }

    return 0;
}
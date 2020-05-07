#include <stdio.h>

int main() {
    int i;  	// an integer value
    int *pi;	// a pointer to an integer value
    
    i = -1;
    pi = &i ;	// set pi to the address of i
    int **ppi;
    ppi = &pi;
    
    printf("i: %d, pi: %p > *pi: %d, ppi: %p > **ppi: %d \n", i, pi, *pi, ppi, **ppi);

    // place additional code here
    
    return 0;    
} 
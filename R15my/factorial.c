#include <stdio.h>

int Param = 0x0004;
int Result;
  
/** Compute N! recursively */
int Factorial(int N) {
  int Temp = N - 1;
  
  if (Temp > 0) { // This is the same as checking if N > 1
    // Recursive call
    return N * Factorial(Temp);
  } else {
    // Base case (N <= 1)
    return 1;
  }
}

/** Entry point */
int main() {
  Result = Factorial(Param);
  printf("Return value is x%04X\n", Result);
  return 0;
}

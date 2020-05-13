/**
 *  @author Bogdan Vasilchenko
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int2char (int radix, int value) {
  if((value > radix-1) || (value < 0)){
    return '?';
  }
  if((radix < 2) || (radix > 36)){
    return '?';
  }


  
  if(radix <= 10){
    char c = '0' + value;
    return c;
  }
  else{
    if(value <= 9){
      char c = '0' + value;
      return c;
    }
    
    char c = ('A')+ (value-10);
    if (c <= 'Z'){
      return c;
    }
    else {
      return '?';
    }
  }
  
 
  
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char2int (int radix, char digit) {
  if ( (radix < 2) || (radix > 36) ) {
    return -1;
  }
  if (radix <= 10 && digit > '0' + (radix-1)) {
      return -1;
    }
  if (radix <= 10){
    
    if(digit >= '0' && digit < '0' + radix ){
      return digit - '0';
    }else {
      return -1;
    }
  }
  
  if (radix > 10){
    
    if(digit >= '0' && digit <= '9'){
      return digit - '0';
    }
    if (digit >= 'A' && digit <= 'A' + (radix-10-1)){
      return (int)digit - 65 +10;
    }else if (digit >= 'a' && digit <= 'a' + (radix-10-1)) {
	return (int) digit - 'a'+10;
      }
      else {
	return -1;
      }
    return -1;
  }

  return -1;

  
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
  *quotient = numerator / divisor;
  *remainder= numerator % divisor;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii2int (int radix, int valueOfPrefix) {
  char c = getchar();
  //base case
  //printf("%c is the char \n",c);
  //printf("%d is the value of prefix\n",valueOfPrefix);
  if (c == '\n'){
    //printf("base case hit!\n");
    return valueOfPrefix;
  }

  if(c >= '0' && c <= '9')
    valueOfPrefix = radix*valueOfPrefix + (c - '0');
    
  
  if(c >= 'A' && c <= 'Z')
    valueOfPrefix = radix*valueOfPrefix + (c- 'A') + 10;
    
  
  if(c >= 'a' && c <= 'z')
    valueOfPrefix = radix*valueOfPrefix + (c- 'a') + 10;
  // ascii2int(radix, valueOfPrefix);
  
  return ascii2int(radix, valueOfPrefix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int2ascii (int radix, int value) {
  if (value == 0){
    return;
  }

  int newVal = value / radix;
  int remainder = value % radix;
  char remChar = 0;
  if (remainder > 9){
    remainder = 'A' + (remainder - 10);
    remChar = (char) remainder;
  } else {
    remChar = (char) (remainder + '0');
  }
  
  int2ascii(radix, newVal);
  putchar(remChar);
  
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac2double (int radix) {
  return -1.0;
}


#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Bogdan</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  int mask = 0b1000000000000000;
  mask = x & mask;
  return (mask >> (BITS-1));
  
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) 
{

  int mask = 0b0111110000000000;
  int new_x = mask & x;
  new_x = new_x >> (BITS-6);

  return new_x;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {

  int mask = 0b0000001111111111;
  iFloat_t last_ten_bits = x & mask;  //just the last 10 bits here
  iFloat_t matissa_w_expl_one = 0b0000010000000000 | last_ten_bits;

  //check if 2's comp negative
  //if negative, then 
  if (floatGetSign(x) == 1)
  {
    iFloat_t matissa_flipped = (~matissa_w_expl_one) + 0b0000000000000001;
    return matissa_flipped;
    
  } 

  return matissa_w_expl_one;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val) {

  *sign = floatGetSign(x);
  *exp = floatGetExp(x);
  *val = floatGetVal(x);

}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
  if(bits == 0){
  return -1;
  }

  //int latest_pos = 15;
for (int i = 15; i >= 0; i--) 
    { 
        int temp = (bits & (0b0000000000000001 << i));
        if (temp != 0)
        {
          return i;
        }
        

        
    } 
return -1;

}



/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  if (x == 0.0){
    return 0.0;
  }
  return (x & 0b0111111111111111);
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
  if (x == 0b0){
    return x;
  }
return x | 0b1000000000000000;
  
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  debug("%s: bits of x (IEEE 754)", getBinary(x)); // example only
  debug("%s: bits of y (IEEE 754)", getBinary(y)); // example only
  debug("%d: x (IEEE 754)", x); // example only
  debug("%d: y (IEEE 754)", y); // example only
  if (x == 0.0){
    return y;
  }
  if (x == 0.0){
    return x;
  }

  
  // Step 1: Extract the  values;
  short int sign_of_x = 0;
  short int sign_of_y = 0;
  short int exp_of_x = 0;
  short int exp_of_y = 0;
  short int val_of_x = 0;
  short int val_of_y = 0;
  int x_largest_exp = 0;
  int y_largest_exp = 0;
  int exps_equal = 0;
  iFloat_t exponent_difference = 0;
  iFloat_t largest_exponent_value = 0;
  //fill in values for x
  floatGetAll(x, &sign_of_x, &exp_of_x, &val_of_x);
  //fill in values for y
  floatGetAll(y, &sign_of_y, &exp_of_y, &val_of_y);
  
  debug("Sign of x = %s",getBinary(sign_of_x));
  debug("Sign of y = %s", getBinary(sign_of_y));
  debug("Exp of X %s", getBinary(exp_of_x));
  debug("Exp of Y %s", getBinary(exp_of_y));
  debug("Val of X %s", getBinary(val_of_x));
  debug("Val of Y %s", getBinary(val_of_y));

  //equalize the exponents correctly;


  //a: fill in values for exponens. Find out which is bigger;
  if (exp_of_x == exp_of_y)
  {
    largest_exponent_value = exp_of_y;
    exponent_difference = 0;
    exps_equal = 1;
  }
  
  else if (exp_of_x > exp_of_y)
  {
    x_largest_exp = 1;
    largest_exponent_value = exp_of_x;
    exponent_difference = exp_of_x - exp_of_y;

  }else
  {
    largest_exponent_value = exp_of_y;
    y_largest_exp = 1;
    exponent_difference = exp_of_y - exp_of_x;
  }
  debug("largest exp value %s", getBinary(largest_exponent_value));
  debug("Largest exp value %d", largest_exponent_value);
  debug("Is exp of x largest? %d", x_largest_exp);
  debug("Exponent Difference %d" , exponent_difference);
  //Equalize exponents;

  //If Exponents are equal, skip equalization;
  if (exps_equal == 0) {
    if (x_largest_exp == 1)
    {
      val_of_y = val_of_y >> exponent_difference;

    }

    if(y_largest_exp == 1){
      val_of_x = val_of_x >> exponent_difference;
    }
    
  }

  debug("New Val Y %s " , getBinary(val_of_y));
  debug("New Val X %s", getBinary(val_of_x));
  //compute the final metissa

  short int val_raw_result = val_of_x + val_of_y;
  debug("new matissa %s", getBinary(val_raw_result));
if (val_raw_result == 0)
  {
    return 0.0;
  }

  short int sign_of_res = 0;
  //perform 2's comp

  if (floatLeftMost1(val_raw_result) == 15){
    debug("performing 2's comp on %s since it's neg", getBinary(val_raw_result));
    val_raw_result = ~val_raw_result + 1;
    sign_of_res = 1;
    debug("done performing 2's comp. the value is now %s", getBinary(val_raw_result));
  }
  
  iFloat_t ready_val = val_raw_result;
  int leftmost_1_of_val = floatLeftMost1(val_raw_result);
  int final_val;
  //shifting to 10 if necassary;
  if (leftmost_1_of_val > 10){
    debug("preparting to shift left leftmost1 to pos 10 of %s now", getBinary(val_raw_result));
    int shift_by = leftmost_1_of_val - 10;
    debug("Will be shifting by %d positions", shift_by);
    ready_val = ready_val >> shift_by;
     debug("shifted leftmost1 to pos 10 now %s", getBinary(ready_val));
    ready_val = ready_val & 0b0000001111111111;
    largest_exponent_value += shift_by;
    final_val = ready_val;
  }
  else if (leftmost_1_of_val < 10){
    debug("preparting to shift right leftmost1 to pos 10 of %s now", getBinary(val_raw_result));
    int amount_of_shift_val = 10 - leftmost_1_of_val;
    debug("Will be shifting by %d positions", amount_of_shift_val);
    short int ready_val = val_raw_result << amount_of_shift_val;
    debug("shifted leftmost1 to pos 10 now %s", getBinary(ready_val));
    ready_val = ready_val & 0b0000001111111111;
    debug("Is the bug here?? %s", getBinary(ready_val));
    largest_exponent_value -= amount_of_shift_val;
    final_val = ready_val;

  } else {
    ready_val = ready_val & 0b0000001111111111;
    final_val = ready_val;
  }
 
  debug("matissa about to be placed in result is %s" ,getBinary(ready_val));
  debug("the other matissa %s", getBinary(final_val));


  short int ready_exp = largest_exponent_value;
  short int ready_sign = sign_of_res;
  debug("Exp of res %s", getBinary(ready_exp << 10));
  debug("Sign of res %s", getBinary(ready_sign));
 
  debug("matissa about to be placed in result is %s" ,getBinary(ready_val));
  short int result = sign_of_res << 15;
  result = result | final_val;
  result = result | (ready_exp << 10);

  
  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {\
  if (x == 0){return y;}
  if (y == 0){return x;}

  if (x < 0 && y < 0){
    debug("got here 1");
    // -x - -y
    return floatAdd(x,floatAbs(y));
  }
  else if(x > 0 && y < 0 ){ 
    // x --y == x + y
    debug("got here 2");
    return floatAdd(x,floatAbs( y));

  }
  else if (x < 0 && y > 0) {
  debug("got here 3");
   // -x - +y == -x + -y
   return floatAdd(x, floatNegate(y));

  } else if (x > 0 && y > 0){
    // x - y = x + -y;
    debug("got here 4");
    return floatAdd(x, floatNegate(y));

  }
  
  return 0.0;
}


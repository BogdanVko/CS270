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
  return x & 0b0111111111111111;
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

  iFloat_t val_raw_result = val_of_x + val_of_y;

if (val_raw_result == 0)
  {
    return 0.0;
  }
  

  debug("Val_raw   %s",getBinary(val_raw_result));
  iFloat_t sign_result = 0;
  iFloat_t val_result_abs = val_raw_result;
  iFloat_t res_exp = largest_exponent_value;
  debug("Final exponent, before shift : %s", getBinary(res_exp));
  //IF THE RESULT IS NEG, GET ABS VAL and 

  //int new_sign = val_raw_result & 0b1000000000000000;
  //debug("new Sign %d", new_sign);
  if (val_raw_result < 0){
    sign_result = 1;
    debug("2s comp val %s", getBinary(val_result_abs)); 
    val_result_abs = (~val_raw_result) + 0b0000000000000001;
  }
  debug("Val_raw after checking for -  %s",getBinary(val_raw_result));
  
  //normalize the metisaa and the exponent
  iFloat_t norm_val = val_result_abs << exponent_difference;
  //res_exp = res_exp - exponent_difference;
  debug("final exponent: %s", getBinary(res_exp));
  iFloat_t mask_for_sign = sign_result << 15;
  iFloat_t mask_for_res_exp = res_exp << 10;
  iFloat_t mask_for_val = norm_val;
  mask_for_val = mask_for_val & 0b1111101111111111;
  debug("Signmask %s ", getBinary(mask_for_sign));
  debug("Exp mask %s ", getBinary(mask_for_res_exp));
  debug("Val Mask %s ", getBinary(mask_for_val));
  iFloat_t result = 0b0000000000000000;
  result = result | mask_for_sign;
  result = result | mask_for_res_exp;
  result = result | mask_for_val;


  return result;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
  return 0;
}


#ifndef __IFLOAT_H__
#define __IFLOAT_H__

/*
 * iFloat.h - header for simple floating point functions.
 *
 * "Copyright (c) 2017 by Fritz Sieker."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE AUTHOR NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
 * UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 */

/** @file iFloat.h
 *  @brief Defines interface of iFloat.c functions (do not modify)
 *  @details This file defines the interface to a C file iFloat.c that
 *  you will complete.  You will learn how to do floating point arithmetic
 *  <b>without using any <code>float</code> variables</b>. Rather you will
 *  perform the operations by using the sign, exponent, and digit fields
 *  as defined in the 
 *  <a href="http://en.wikipedia.org/wiki/IEEE_floating_point">IEEE Floating
 *  Point Standard</a>.
 *  <p>
 *  Everything in a computer is stored as a series of 0/1's. When you use an
 *  <code>int</code> to type a value, you are telling the compiler (and
 *  ultimately the CPU) to treat the 0/1's as a two's complement number. When
 *  you use <code>float</code>, the 0/1's represent a floating point number.
 *  When an addition is performed, the computer knows whether to use the
 *  integer or floating point add instruction. The two instructions do different
 *  things to the 0/1's. <p> In this assignment, you are doing floating point
 *  operations  <b>without</b> using floating point instructions. You are
 *  directly doing the bit manipulations necessary to complete the add. Since
 *  <code>iFloat_t</code> is an integral type, the compiler will generate integer
 *  instructions. The <code>iFloat_t</code> is to remind you (the programmer),
 *  that although the computer is going to treat all values as integers, you
 *  know it is really 3 values (sign, exponent, mantissa) packed into a single
 *  integer number. Your responsibility is to unpack the three pieces, do the
 *  operations necessary to complete the operation, then put the three pieces
 *  back together.
 */

#ifdef HALF
typedef short iFloat_t;

#define BITS      16
#define BITS_EXP   5
#define BITS_MANT 10
#define EXP_BIAS  15

#else
typedef int iFloat_t;

#define BITS      32
#define BITS_EXP   8
#define BITS_MANT 23
#define EXP_BIAS  127

#endif

/** Extract the sign of the argument.
 *  @param x the integer containing an IEEE floating point value
 *  @return 0 if the value is 0 or positive, 1 if it is negative
 */
iFloat_t floatGetSign (iFloat_t x);

/** Extract the exponent of the argument.
 *  @param x the integer containing an IEEE floating point value
 *  @return the biased exponent of the argument
 */
iFloat_t floatGetExp (iFloat_t x);

/** Extract the value of the argument. The value is the mantissa with the
 *  implicit 1 made explicit and adjusted for the sign of the argument. Please
 *  refer to the floating point addition example (step 1) in the instructions for
 *  an example on how the value is extracted. Basically, you'll have to do three
 *  things: 1) extract the mantissa; 2) set the implicit 1 in the extracted
 *  mantissa; 3) if the sign of the argument is negative, return the 2's complement
 *  of the mantissa from step (2). Otherwise, return it as-is. You may want to use
 *  the <code>getField</code> function from R3.
 *  @param x the integer containing an IEEE floating point value
 *  @return the bits representing the value. If x represents 0.0, you should still
 *  set the implicit 1 in the extracted mantissa.
 */
iFloat_t floatGetVal (iFloat_t x);

/** Get the sign, exponent, and value in a single call.
 *  @param x the integer containing an IEEE floating point value
 *  @param sign pointer to location where the sign will be stored
 *  @param exp pointer to location where the exponent will be stored
 *  @param val pointer to location where the value will be stored
 */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t*exp, iFloat_t* val);

/** Obtain the position of the leftmost 1 in the argument's bits.
 *  @param bits the integer
 *  @return -1 if the value is 0, otherwise the position (0 to 15) of the
 *  leftmost 1 bit. In a binary number, the positions are numbered from right to
 *  left with the rightmost position being 0.
 */
iFloat_t floatLeftMost1 (iFloat_t bits);

/** Absolute value of the argument. This can be done with a simple bit
 *  manipulation operation. No conditionals are required.
 *  @param x the integer containing an IEEE floating point value
 *  @return the absolute value of the parameter
 */
iFloat_t floatAbs (iFloat_t x);

/** Negate the argument. This can be done with a simple bit manipulation
 *  function. No conditionals are required. This is NOT the bitwise negation
 *  of the argument. As an example, if the argument represents 2.25, this function
 *  should return the IEEE bit pattern for -2.25.
 *  @param x the integer containing an IEEE floating point value
 *  @return the negation of the value. Note that the negation of 0.0 is 0.0 (not
 *  -0.0).
 */
iFloat_t floatNegate (iFloat_t x);

/** Add two floating point values.
 *  @param x an integer containing an IEEE floating point value
 *  @param y an integer containing an IEEE floating point value
 *  @return x + y. Your code needs to account for a value of 0.0, but no other
 *  special cases (e.g. infinities).
 */
iFloat_t floatAdd (iFloat_t x, iFloat_t y);

/** Subtract two floating point values.
 *  @param x an integer containing an IEEE floating point value
 *  @param y an integer containing an IEEE floating point value
 *  @return x - y. Your code needs to account for a value of 0.0, but no other
 *  special cases (e.g. infinities).
 */
iFloat_t floatSub (iFloat_t x, iFloat_t y);

#endif

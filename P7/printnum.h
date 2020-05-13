#ifndef __PRINTNUM_H__
#define __PRINTNUM_H__

/*
 * printnum.h - simple functions to print a number using recursion.
 *
 * "Copyright (c) 2013-15 by Your name goes here."
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

/** @file printnum.h
 *  @brief Defines interface of printnum.c functions (do not modify)
 *  @details This file defines the interface to a C file printnum.c that
 *  you will complete. You will learn how to use the C language operators
 *  for address-of (<b>&amp;</b>), and dereferencing pointers <b>*</b>). 
 *  This will serve as a model when you implement the same functions in LC3
 *  assembly language.
 */

/** A string of characters representing the digits to output for a particular
 *  value. Defined in the file <code>testPrint.c</code>.
 */
extern char* digits;

/** Return the character corresponding to the digit. 
 *  Use <code>val</code> as an index into the string <code>digits</code>
 *  @param val - a value in the range of <code>0 - (base-1)</code>
 *  @return - character '0' .. '9' or 'A'..'Z'
 */
char getDigit (int val);

/** Calculate both the quotient and remainder of a division and return the
 *  values via pointers. You may use the C operators for division (<b>/</b>)
 *  and modulus (<b>%</b>). However, you might want to write a loop to
 *  using repeated subtraction do the calculations to help you understand how
 *  you will implement this in LC3 assembly language (which has no operators
 *  for division or modulus).
 *  @param numerator - non-negative value for numerator
 *  @param divisor - a positive value to divide by
 *  @param quotient - a pointer to the location to store the result of division
 *  @param remainder - a pointer to the location to store the remainder
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder);
/**
  *quotient = numerator / divisor;
  *remainder= numerator % divisor;
}**/


/** Print a number in the specified base. Use the C call <code>putchar()</code>
 *  to print a single character obtained using <code>getDigit()</code>.
 *  This corresponds to the <code>OUT</code> instruction of the LC3 OS. You may
 *  not use any other C I/O routine for printing. This function <b>MUST</b> be
 *  implemented recursively.
 *  @param x - the number to print
 *  @param base - the base in which the number should be printed
 */
void printNum (int x, int base);

#endif

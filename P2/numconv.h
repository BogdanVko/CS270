#ifndef __NUMCONV_H__
#define __NUMCONV_H__

/*
 * numconv.h - simple functions to convert between internal/external
 * representations of numbers
 *
 * "Copyright (c) 2013-16 by Fritz Sieker."
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

/** @file numconv.h
 *  @brief Defines interface of numconv.c functions (do not modify)
 *  @details This file defines the interface to a C file numconv.c that
 *  you will complete. You will learn how to use the C language operators
 *  for address-of (<b>&amp;</b>), and dereferencing pointers <b>*</b>).
 */

/** Return the character corresponding to a value.
 *  <p><span style="color: red;"><b>This function should not print anything (you
 *  will lose all points for this function if it does). However, you may print
 *  stuff for your own debugging purposes as long as you remove any printing
 *  statements before you submit.</b></span></p>
 *  @param radix - the base you are working in (2-36)
 *  @param value - a value in the range of <code>0 - (radix-1)</code>
 *  @return - character '0'..'9' or 'A'..'Z' corresponding to the given value
 *  if the value is legal in the given radix. Otherwise return character '?'
 */
char int2char (int radix, int value);

/** Return the value corresponding to a character.
 *  <p><span style="color: red;"><b>This function should not print anything (you
 *  will lose all points for this function if it does). However, you may print
 *  stuff for your own debugging purposes as long as you remove any printing
 *  statements before you submit.</b></span></p>
 *  @param radix - the base you are working in (2-36)
 *  @param digit - character '0'..'9' or 'A'..'Z' or 'a'..'z'
 *  @return - value in the range of <code>0 - (radix-1)</code> corresponding to
 *  the given digit if the digit is valid in the given radix. Otherwise return
 *  -1
 */
int char2int (int radix, char digit);

/** Calculate both the quotient and remainder of a division and return the
 *  values via pointers. You may use the C operators for division (<b>/</b>)
 *  and modulus (<b>%</b>). However, you might want to write a loop to
 *  perform repeated subtraction to help you understand how you would implement
 *  this in LC3 assembly language (which has no operators for division or
 *  modulus).
 *  <p><span style="color: red;"><b>This function should not print anything (you
 *  will lose all points for this function if it does). However, you may print
 *  stuff for your own debugging purposes as long as you remove any printing
 *  statements before you submit.</b></span></p>
 *  @param numerator - non-negative value for numerator
 *  @param divisor - a positive value to divide by
 *  @param quotient - a pointer to the location in which to store the quotient
 *  @param remainder - a pointer to the location in which to store the remainder
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder);

/** Convert a string to an integer value. The string comes from the standard
 *  input. You must read one character at a time by using the
 *  built-in <code>getchar()</code> function which simply returns the next
 *  character available in the standard input. The end of the string is signaled
 *  by a newline character ('\\n'). You <b>MUST</b> implement this function
 *  recursively. That means you shouldn't have loops. For information on the
 *  algorithm, see the Example revisited (page 3) on Sanjay's handout titled
 *  "Number Systems" (referenced in the main page). You may assume that the
 *  string is legal in the given radix (letters may be uppercase or lowercase).
 *  You can also assume that the string represents a non-negative number.
 *  Here's an example for how to test this function:
 *  <p><code>echo "48A6" | ./testConv a2i 12</code></p>
 *  This ensures that the string "48A6" is available for you to read from the
 *  standard input. The first time you call <code>getchar()</code>, it will
 *  return '4'. The second time, it will return '8', and so on. Eventually, it
 *  will return '\\n' (because the <code>echo</code> command automatically
 *  appends a newline character).
 *  <p><span style="color: red;"><b>This function should not print anything (you
 *  will lose all points for this function if it does). However, you may print
 *  stuff for your own debugging purposes as long as you remove any printing
 *  statements before you submit.</b></span></p>
 *  @param radix - the base you are working in (2-36)
 *  @param valueOfPrefix - the integer value of the digits processed so far (the
 *  prefix). For example, if the string is "48A6" in base 12 and you're about to
 *  read 'A', the prefix is "48" and the integer value of this prefix is 56.
 *  When your function is called by the main program (the testConv.c file),
 *  this parameter is 0.
 *  @return the number represented by the string
 */
int ascii2int (int radix, int valueOfPrefix);

/** Print a number in the specified radix. Use the C call <code>putchar()</code>
 *  to print a single character obtained using <code>int2char()</code>. Do not
 *  use any other output functions. This function <b>MUST</b> be implemented
 *  recursively. <b>Your program can not use arrays or strings in C, even if you
 *  know about them.</b> For information on the algorithm, see Section 3 (page
 *  5) on Sanjay's handout titled "Number Systems" (referenced in the main
 *  page). See also Section A2 in the "Number Conversion" notes by Fritz
 *  (referenced in the main page).
 *  <p><span style="color: red;"><b>This function should only print the digits
 *  of the number. If it prints extra stuff, you will lose all points for this
 *  function. Do not print a newline character at the end. You may print stuff
 *  for your own debugging purposes as long as you remove any extra printing
 *  statements before you submit.</b></span></p>
 *  <p><span style="color: red;"><b>Also, make sure this function does not
 *  print leading zeroes (if it does, you will lose all points for this
 *  function).</b></span></p>
 *  @param radix - the base you are working in (2-36)
 *  @param value - the number to convert (it will be non-negative)
 */
void int2ascii (int radix, int value);

/** Convert a string representing the fractional part of a number into a
 *  double. <b>This function is for extra credit.</b> The string comes from the
 *  standard input. You must read one character at a time by using the
 *  built-in <code>getchar()</code> function which simply returns the next
 *  character available in the standard input. The end of the string is signaled
 *  by a newline character ('\\n'). You <b>MUST</b> implement this function
 *  recursively. That means you shouldn't have loops. For information on the
 *  algorithm, see Section 4 (page 8) on Sanjay's handout titled "Number
 *  Systems" (referenced in the main page). You may assume that the string is
 *  legal in the given radix (letters may be uppercase or lowercase). The string
 *  that is provided in the standard input will start with <code>0.</code> (a zero
 *  followed by a radix point). However, you should assume that everything up to
 *  (and including) the radix point has been read. Hence, the first time you call
 *  <code>getchar()</code>, you will get the first character after the radix point.
 *  Here's an example for how to test this function:
 *  <p><code>echo "0.B5C" | ./testConv f2d 13</code></p>
 *  This ensures that the string "B5C" is available for you to read from the
 *  standard input. The first time you call <code>getchar()</code>, it will
 *  return 'B'. The second time, it will return '5', and so on. Eventually, it
 *  will return '\\n' (because the <code>echo</code> command automatically
 *  appends a newline character).
 *  <p><span style="color: red;"><b>This function should not print anything (you
 *  will lose all points for this function if it does). However, you may print
 *  stuff for your own debugging purposes as long as you remove any printing
 *  statements before you submit.</b></span></p>
 *  @param radix - the base you are working in (2-36)
 *  @return the value of the fractional part as a double.
 */
double frac2double (int radix);

#endif

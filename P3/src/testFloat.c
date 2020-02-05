/*
 * testFloat.c - simple driver to test methods of iFloat.h.
 *
 * "Copyright (c) 2012-2017 by Fritz Sieker."
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "Debug.h"
#include "convert.h"
#include "iFloat.h"

/** @mainpage CS270 Programming Assignment P3 - Floating Point Math
 *  \htmlinclude "FLOAT.html"
 */

/** @file: testFloat.c
 *  @brief Driver to test functions of iFloat.c (do not modify)
 *
 * @details This is a driver program to test the functions
 * defined in iFloat.h and implemented in iFloat.c. The program takes one
 * or more command line parameters and calls one of the methods, then
 * prints the results. To see how to use the program, execute
 * <code>testFloat</code> in a terminal window. This will print a usage
 * statement defining how to run the program. The first "logical" parameter of
 * the program is always a key defining which function to run. It may be
 * optionally preceeded by <code>-debug</code> to turn on debugging. The
 * options are:
 * <ul>
 * <li><b>abs</b> absolute value of a floating point number </li>
 * <li><b>all</b> extract sign, exponent, value of a floating point number</li>
 * <li><b>add</b> add two floating point numbers </li>
 * <li><b>bin</b> print binary representation of floating point number </li>
 * <li><b>exp</b> extract exponent of a floating point number </li>
 * <li><b>lm1</b> find the leftmost 1 bit in number</li>
 * <li><b>neg</b> negate a floating point number </li>
 * <li><b>sign</b> extract sign of floating point number</li>
 * <li><b>sub</b> subtract two floating point numbers</li>
 * <li><b>val</b> extract value of floating point number</li>
 * </ul>
 * <p>
 * A sample execution might be: <code>testFloat abs -2.5</code>
 * <p>
 * which prints <pre><code>abs(-2.5) --> 2.500000</code></pre>
 * <p>
 * To use the <code>bin</code> option do <code>testFloat bin 1.5</code>
 * <p>
 * which prints <pre><code>dec: 15872  hex: 0x3E00  bin: 0011-1110-0000-0000</code></pre>
 * <p>
 * This is the decimal, hex and binary representation of the floating point
 * number 1.5. You will find the <code>bin</code> option very useful as you
 * can determine what the correct representation of the answer should be. To
 * test you program, choose values where the correct answer is easy to compute
 * in your head. Then use the <code>bin</code> option to determine what the
 * answer looks like. Finally, run your program and if your answer differs
 * from the answer you computed, use the <code>bin</code> option to see the
 * pattern of your answer. Then you need to read your program, perhaps add
 * debugging output (using the <code>debug()</code> function), and determine
 * what your program is actually doing.
 * <p>
 * @author Fritz Sieker
 */

/** Get the binary representation of a value starting at the specified
 * bit position. A separator is printed every 4 bits for easy reading.
 * This function return a pointer to a static buffer, so that the result
 * must be used, before it is called again. In particular, you may <b>NOT</b>
 * have multiple calls to this function in a single <tt>DEBUG()</tt> call.
 * @param value the value to be converted to binary
 * @param msb the bit position to begin printing (31 to 0)
 * @return a string of bits with a separator every four characters
 */
const char* getBinaryMSB (int value, int msb) {
  static char bits[48];
  int i = 0;

  while (msb >= 0) {
    bits[i++] = ((value & (1 << msb)) ? '1' : '0');

    if (msb && ((msb & 0x3) == 0))
      bits[i++] = '-';
    msb--;
  }

  bits[i] = '\0'; // terminate string

  return bits;
}

/** Get a 16/32 bit binary representation of a value.
 * @param value the value to be converted to binary
 * @return a string of bits with a separator every four characters
 */
const char* getBinary (iFloat_t value) {
  return getBinaryMSB(value, BITS-1);
}

/** Print a usage statement, then exit the program returning a non zero
 * value, the Linux convention indicating an error
 */
static void usage() {
  puts("usage: testFloat [-debug] abs FPvalue");
  puts("       testFloat [-debug] all FPvalue");
  puts("       testFloat [-debug] add FPvalue1 FPvalue2");
  puts("       testFloat [-debug] bin FPvalue");
  puts("       testFloat [-debug] exp FPvalue");
  puts("       testFloat [-debug] lm1 Intvalue");
  puts("       testFloat [-debug] neg FPvalue");
  puts("       testFloat [-debug] sign FPvalue");
  puts("       testFloat [-debug] sub FPvalue1 FPvalue2");
  puts("       testFloat [-debug] val FPvalue\n");
  exit(1);
}

/** Entry point of the program
 * @param argc count of arguments, will always be at least 1
 * @param argv array of parameters to program argv[0] is the name of
 * the program, so additional parameters will begin at index 1.
 * @return 0 the Linux convention for success.
 */
int main (int argc, const char* argv[]) {
  iFloat_t x, y;

  debugInit(&argc, argv);

  if (argc < 3) {
    usage();
  }

  const char* op = argv[1];

  x = toiFloat(argv[2]);

  if (argc > 3)
    y = toiFloat(argv[3]);

  if ((strcmp(op, "abs") == 0) && (argc == 3)) {
    printf("abs(%s) --> %f\n", argv[2], fromiFloat(floatAbs(x)));
  }

  else if ((strcmp(op, "all") == 0) && (argc == 3)) {
    iFloat_t sign, exp, val;
    floatGetAll(x, &sign, &exp, &val);
    printf("sign: %d exp: %d val: %s\n", sign, exp, getBinary(val));
  }

  else if ((strcmp(op, "add") == 0) && (argc == 4)) {
    printf("%s + %s --> %f\n", argv[2], argv[3], fromiFloat(floatAdd(x, y)));
  }

  else if ((strcmp(op, "bin") == 0) && (argc == 3))  {
    printf("dec: %d  hex: 0x%X  bin: %s\n", x, x, getBinary(x));
  }

  else if ((strcmp(op, "exp") == 0) && (argc == 3)) {
    printf("exp %s --> %d\n", argv[2], floatGetExp(x));
  }

  else if ((strcmp(op, "lm1") == 0) && (argc == 3)) {
    printf("%d\n", floatLeftMost1(x));
  }

  else if ((strcmp(op, "neg") == 0) && (argc == 3)) {
    printf("neg(%s) --> %f\n", argv[2], fromiFloat(floatNegate(x)));
  }

  else if ((strcmp(op, "sign") == 0) && (argc == 3)) {
    printf("sign(%s) --> %d\n", argv[2], floatGetSign(x));
  }

  else if ((strcmp(op, "sub") == 0) && (argc == 4)) {
    printf("%s - %s --> %f\n", argv[2], argv[3], fromiFloat(floatSub(x, y)));
  }

  else if ((strcmp(op, "val") == 0) && (argc == 3)) {
    printf("val(%s) --> %s\n", argv[2], getBinary(floatGetVal(x)));
  }

  else
    usage();
  
  return 0;
}

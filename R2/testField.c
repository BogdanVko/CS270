/*
 * testField.c - simple driver to test methods of field.h.
 *
 * "Copyright (c) 2013 by Fritz Sieker."
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
#include "field.h"

/** @mainpage CS270 Recitation R2 - Bit Fields in C
 *  \htmlinclude "R2.html"
 */

/** @file: testField.c
 *  @brief Driver to test functions of field.c (do not modify)
 *
 * @details This is a driver program to test the functions
 * defined in field.h and implemented in field.c. The program takes one
 * or more command line parameters and calls one of the methods, then
 * prints the results. To see how to use the program, execute
 * <code>testField</code> in a terminal window. This will print a usage
 * statement defining how to run the program. The first parameter of the
 * program is always a key defining which function to run. The
 * options are:
 * <ul>
 * <li><b>bin</b> print the next parameter in decimal, hex and binary</li>
 * <li><b>getBit</b> gets the specified bit from a binary value (2 more parameters)</li>
 * <li><b>setBit</b> sets the specified bit in a binary value to 1 (2 more parameters)</li>
 * <li><b>clearBit</b> sets the specified bit in a binary value to 0 (2 more parameters)</li>
 * <li><b>getField</b> get a field from a value (4 more parameters)</li>
 * </ul>
 * <p>
 * A sample execution might be: <code>testField getField 0xABCD 9 4 0</code>
 * <p>
 * which prints <pre><code>getField: get bits 9:4 from 0xABCD (sign 0) = 0x3C</code></pre>
 * <p>
 * All values may be entered as signed decimal numbers or as hex values
 * by beginning it with <code>0x</code>.
 * <p>
 * @author Fritz Sieker
 */

/** Print the binary representation of a value starting at the specified
 * bit position. A separator is printed every 4 bits for easy reading.
 * @param value the value to be printed
 * @param msb the bit position to begin printing (31 to 0)
 */
void printBinaryMSB (int value, int msb) {
  while (msb >= 0) {
    putchar(((value & (1 << msb)) ? '1' : '0'));
    if (msb && ((msb & 0x3) == 0))
      putchar('-');
    msb--;
  }
}

/** Print a 32 bit binary representation of a value.
 * @param value the value to be printed
 */
void printBinary (int value) {
  printBinaryMSB(value, 31);
}

/** Print a usage statement, then exit the program returning a non zero
 * value, the Linux convention indicating an error
 */
static void usage() {
  puts("Usage: testField bin value");
  puts("       testField getBit value position");
  puts("       testField setBit value position");
  puts("       testField clearBit value position");
  puts("       testField getField value hi lo isSigned");
  exit(1);
}

/** print the value in decimal, hex and binary.
 * @param result the value to be printed.
 */
static void printResult (int result) {
  printf("dec: %d hex: 0x%X bin: ", result, result);
  printBinary(result);
  printf("\n");
}

/** Entry point of the program
 * @param argc count of arguments, will always be at least 1
 * @param argv array of parameters to program argv[0] is the name of
 * the program, so additional parameters will begin at index 1.
 * @return 0 the Linux convention for success.
 */
int main (int argc, char* argv[]) {
  char* junk;
  int   value, result, position, hi, lo;
  bool isSigned;

  if (argc < 3)
    usage();
  
  char* op = argv[1];

  if ((strcmp(op, "bin") == 0) && (argc == 3)) {
    printResult((int) strtol(argv[2], &junk, 0));
  }

  else if ((strcmp(op, "getBit") == 0) && (argc == 4)) {
    value    = (int) strtol(argv[2], &junk, 0);
    position = (int) strtol(argv[3], &junk, 0);
    result   = getBit(value, position);
    printf("getBit %d from 0x%x = %d\n", position, value, result);
  }

  else if ((strcmp(op, "setBit") == 0) && (argc == 4)) {
    value    = (int) strtol(argv[2], &junk, 0);
    position = (int) strtol(argv[3], &junk, 0);
    result   = setBit(value, position);
    printf("setBit %d in 0x%x = 0x%x\n", position, value, result);
  }

  else if ((strcmp(op, "clearBit") == 0) && (argc == 4)) {
    value    = (int) strtol(argv[2], &junk, 0);
    position = (int) strtol(argv[3], &junk, 0);
    result   = clearBit(value, position);
    printf("clearBit %d in 0x%x = 0x%x\n", position, value, result);
  }

  else if ((strcmp(op, "getField") == 0) && (argc == 6)) {
    value    = (int) strtol(argv[2], &junk, 0);
    hi       = (int) strtol(argv[3], &junk, 0);
    lo       = (int) strtol(argv[4], &junk, 0);
    isSigned = (bool) strtol(argv[5], &junk, 0);
    result   = getField(value, hi, lo, isSigned);
    printf("getField: get bits %d:%d from 0x%X (signed %d) = 0x%X\n", hi, lo, value, isSigned, result);
  }

  else
    usage();
  
  return 0;
}


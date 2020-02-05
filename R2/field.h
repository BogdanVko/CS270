#ifndef __FIELD_H__
#define __FIELD_H__

/*
 * field.h - simple field manipulation functions to get students working
 *           with masking. This will be used in the simulator to extract
 *           information when executing an LC3 instruction. It may also be
 *           used in the assembler to "create" the 16 bit LC3 instructions.
 *           If an assignment involving floating point manipulation (e.g.
 *           16 bit floating point addition), this file can be used to
 *           provide support routines for extracting/setting the sign,
 *           exponent, and mantissa fields.
 *
 * "Copyright (c) 2013 by Fritz Sieker."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software,
 * that the files COPYING and NO_WARRANTY are included verbatim with
 * any distribution, and that the contents of the file README are included
 * verbatim as part of a file named README with any distribution.
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

/** @file field.h
 *  @brief Defines interface of field.c functions (do not modify)
 *  @details This file defines the interface to a C file field.c that
 *  you will complete.  You will learn how to
 *  use the C language operators for binary <b>and</b> (<b>&amp;</b>),
 *  binary <b>or</b> (<b>|</b>), and binary <b>not</b> (<b>~</b>). You will also use the
 *  C language <b>bit shift</b> operators (<b>&lt;&lt;</b> and <b>&gt;&gt;</b>).
 *  @author Fritz Sieker
 */
#include <stdbool.h>
/** Get the specified bit from a value.
 *  @param value the source value or bit pattern
 *  @param position the bit position to get (0..31)
 *  @return 1 when the bit is set, and 0 otherwise.
 */
int getBit (int value, int position);

/** Set the specified bit in a value (make it equal to 1).
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the specified bit
 *  set.
 */
int setBit (int value, int position);

/** Clear the specified bit in a value (make it equal to 0).
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the specified bit
 *  cleared.
 */
int clearBit (int value, int position);

/** Extract the field (possibly signed) between bits hi and lo (inclusive).
 *  @param value  the source value or bit pattern
 *  @param hi the bit position of one end of the field
 *  @param lo the bit position of the other end of the field
 *  @param isSigned false means the field is unsigned, true means the field is signed
 *  @return The value of the field.  Sanity check example:
 *  if the field is three bits wide and unsigned, the result
 *  will be a value between 0 and 7, regardless of the actual position of the
 *  bits in value. If the value is signed, the result will be between -4 and 3.
 *  Furthermore, if the value is signed, it will be negative <b>only</b> if
 *  the left most bit of the field is 1. In this case, the field must be
 *  sign extended (i.e. make all bits to the left 1).
 */
int getField (int value, int hi, int lo, bool isSigned);

#endif


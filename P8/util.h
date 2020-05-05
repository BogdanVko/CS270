#ifndef __UTIL_H__
#define __UTIL_H__

/*
 * "Copyright (c) 2012-2016 by Fritz Sieker."
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

/** @file util.h
 *  @brief Defines interface to utility functions for LC3 assembler (do not modify).
 *  @details This defines the interface to some utilities for the LC3
 *  assembler. In completing the corresponding .c file, you will learn
 *  how to encode information in data structures, rather than directly in
 *  "code". You will also learn how to do some simple character processing.
 *  <p>
 *  @author Fritz Sieker
 */

#include <stdbool.h>

#include "lc3.h"

/** Define a mapping between a name and an integer value */
typedef struct name_val {
  char* name;  /**< Human readable name of value (e.g. "ADD") */
  int   val;   /**< Corresponding numeric value (e.g. OP_ADD) */
} name_val_t;
  
/** Search a sorted list of items for a given name. The names are case
 *  insensitive, so the name "foo" and "Foo" match. This function is only
 *  used in util.c, but is declared here for documentation purposes.
 *  @param map - a sorted array of values
 *  @param numNames - number of entries in the array
 *  @param name - the name to search for (case insensitive)
 *  @return NULL if the name is not in the list, or a pointer to the
 *  name/value pair.
 */
name_val_t* util_bin_search (name_val_t map[], int numNames, const char* name);

/** Get the opcode associated with an LC3 op (e.g. "ADD")
 *  @param name - name of operand (e.g. <code>"ADD"</code>)
 *  @return the opcode for this name (e.g. <code>OP_ADD</code>), or OP_INVALID
 *  if the name is not an LC3 opcode, or pseudo-op
 *  information about that instruction
 */
opcode_t util_get_opcode (const char* name);

/** Determine if a string is a valid label or not. Valid labels beging with
 *  a letter or '_' and may contain only letters, digits and ('_').
 *  You may find the C header <code>ctype.h</code> useful.
 *  @param s - ths string to validate (e.g. <code>"Some_label"</code>)
 *  @return <code>false</code> if the string is <b>not</b> valid,
 *  <code>rrue</code> if it is valid.
 */
bool util_is_valid_label(const char* s);

/** Determine if the string represents a valid register specification
 *  A register is specified by the letter 'R' (case insensitive) followed by a
 *  digit 0 to 7.
 *  @param regStr - the string to check
 *  @return the register number if the string is a valid register, or -1 if it
 *  is not.
 */
int util_get_reg (const char* regStr);

/** Determine the condition code associated with the string. The string
 *  consists of of 0 to 3 three characters, with no more that one each
 *  character from the set 'nzp' (case insensitive). The values must follow
 *  that order. That is, if 'n' is present it MUST proceed 'z' and/or 'p'.
 *  If 'z' is present, in must preceed 'p'.
 *  @param condCodeStr - the string to parse (e.g. <code>"zp"</code>)
 *  @return - the value (1-7) representing the condition code or -1 if the
 *  condCodeStr is not valid.
 */
int util_parse_cond (const char* condCodeStr);

/** Convert a string to an integer using the LC3 syntax for constants.
 *  The LC3 format assumes hex <b>unless</b> the string is preceeded by a
 *  &# sign to indicate decimal values. The initial x/X for hex values is
 *  optional. Hex values may be preceeded by a '-'.
 *  @param token - the string to be converted
 *  @param value - pointer to where value will be stored
 *  @return true on success, false on failure
 */
bool util_get_int (const char* token, int* value);

#endif

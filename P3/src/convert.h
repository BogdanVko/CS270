#ifndef  __CONVERT_H__
#define __CONVERT_H__

#include "iFloat.h"

/** @file convert.h
 *  @brief Defines interface of convert.c functions (do not modify)
 *  @details This file defines the interface to a C file convert.c that
 *  converts between <code>float</code> and <code>iFloat_t</code> types.
 *  Thus, you do not need to declare <b>ANY</b> <code>float</code> variables
 *  anywhere in your code. Note that the test driver <code>testFloat.c</code>
 *  does not use any <code>float</code> variables.
 */

/** Convert a string to a <code>iFloat_t</code>
 *  @param str the string to convert
 *  @return an iFloat_t containing the IEEE floating point value
 */
iFloat_t toiFloat (const char* str);

/** Convert a <code>iFloat_t</code> to a <code>float</code>
 *  @param x the iFloat_t containing bits for a IEEE floating point value
 *  @return the value as a <code>float</code>
 */
float fromiFloat (iFloat_t x);

#endif

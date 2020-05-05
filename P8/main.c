/*
 * "Copyright (c) 2014 by Fritz Sieker."
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
/** @mainpage cs270 Programming Assignment - LC3 Assembler
 *  \htmlinclude "assembler.html"
 */

/** @file main.c
 *  @brief Driver for the lc3 assembler (do not modify)
 *  @details This file is a driver for the lc3 assembler and contains main().
 *  The basic flow of the function is:
 *  <ol>
 *  <li>validte the program arguments</li>
 *  <li>call <code>asm_init()</code></li>
 *  <li>call <code>asm_pass_one()</code></li>
 *  <li>report then number of errors found in the first pass. If
 *  there were no errors, call <code>asm_pass_two()</code></li>
 *  <li>report the number of errors found in the second pass</li>
 *  <li>call <code>asm_term()</code></li>
 *  </ol>
 *  The program return <code>0</code> if no errors were found, non-zero 
 *  otherwise.
 * <p>
 * @author <b>Fritz Sieker</b>
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/** force instantiation of LC3AS_VAR variables in this file */
#define LC3AS_VAR

#include "Debug.h"
#include "assembler.h"

/** print usage statement for program */
static void usage (void) {
  fprintf(stderr, "Usage: [my]lc3as [-d] [-hex] [-pass1] <ASM filename>\n");
  fprintf(stderr, "  -d turns on debugging\n");
  fprintf(stderr, "  -hex produces a .hex file instead of .obj file\n");
  fprintf(stderr, "  -pass1 produces debug output from asm_pass_one()\n");
  exit (1);
}

/** The entry point of the assembler. The program is invoked using:
 *  <pre><code>
 *  [my]lc3as [-hex] [-pass1] assembly_file_name
 *  </code></pre>
 *  @param argc - count of arguments
 *  @param argv - an array of arguments
 */
int main (int argc, const char* argv[]) {
  debugInit(&argc, argv);

  int   asm_arg  = argc - 1;
  const char* asm_file = argv[asm_arg];
  bool  isHex    = false;

  printPass1 = 0;

  if (! lc3_file_has_suffix(asm_file, ".asm"))
    usage(); // this exits

  for (int i = 1; i < asm_arg; i++) {
    if (strcmp(argv[i], "-hex") == 0)
      isHex = true;
    else if (strcmp(argv[i], "-pass1") == 0)
      printPass1 = 1;
    else
      usage(); // this exits
  }

  debug("'%s' invoked with %d parameters\n", argv[0], argc); // demo DEBUG

  asm_init();

  char* obj_file = lc3_replace_suffix(asm_file, (isHex ? ".hex" : ".obj"));
  char* sym_file = lc3_replace_suffix(asm_file, ".sym");

  printf("STARTING PASS 1\n");
  line_info_t* list = asm_pass_one(asm_file, sym_file);

  printf("%d errors found in first pass\n\n", numErrors);

  if (numErrors == 0) {
    printf("STARTING PASS 2\n");
    lc3_set_obj_file_mode(obj_file);
    asm_pass_two(obj_file, list);

    printf("%d errors found in second pass\n", numErrors);
  }

  if (numErrors > 0) {
    remove(obj_file); // errors ignored
    remove(sym_file); // errors ignored
  }

  free(obj_file);
  free(sym_file);

  asm_term(list);

  return (numErrors != 0);
}

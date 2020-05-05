/** @file assembler.c
 *  @brief You will modify this file and implement the assembler.h interface
 *  @details This is a implementation of the interface that you will write
 *  for the assignment. Although there are only four functions defined
 *  by the interface, it is likely that you will add many helper functions
 *  to perform specific tasks.
 *  <p>
 *  @author <b>your name here</b>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <assert.h>

#include "assembler.h"
#include "lc3.h"
#include "symbol.h"
#include "tokens.h"
#include "util.h"

/** Global variable containing the current line number in the source file*/
static int srcLineNum;

/** Global variable containing the current LC3 address */
static int currAddr;

// You may modify the body of this function if that you want to.
// Just think about what might be useful to do.

line_info_t* asm_init_line_info (line_info_t* info, const char* opTok) {
  if (! info)
    info = malloc(sizeof(line_info_t));

  info->next        = NULL;
  info->lineNum     = srcLineNum;
  info->address     = currAddr;
  info->opcode      = OP_INVALID;
  info->format      = NULL;
  info->DR          = -1;
  info->SR1         = -1;
  info->SR2         = -1;
  info->immediate   = 0;
  info->reference   = NULL;

  return info;
}

// do not modify
void asm_print_line_info (line_info_t* info) {
  if (printPass1 && info) {
    printf("%3d: addr: x%04x op: %-10s DR:%3d, SR1:%3d SR2:%3d imm: %d ref: %s\n",
           info->lineNum, info->address, lc3_get_opcode_name(info->opcode), info->DR,
           info->SR1, info->SR2, info->immediate, info->reference);
  }
}

// do not modify
/* based on code from http://www.eskimo.com/~scs/cclass/int/sx11c.html */
void asm_error (const char* msg, ...) {
  numErrors++;
  va_list argp;
  fprintf(stderr, "%3d: ERROR - ", srcLineNum);
  va_start(argp, msg);
  vfprintf(stderr, msg, argp);
  va_end(argp);
  fprintf(stderr, "\n");
}

/** @todo implement this function */
void asm_init (void) {
}

/** @todo implement this function */
line_info_t* asm_pass_one (const char* asm_file_name,
                           const char* sym_file_name) {

  return NULL;
}

/** @todo implement this function */
void asm_pass_two (const char* obj_file_name, line_info_t* list) {
}

/** @todo implement this function */
void asm_term (line_info_t* list) {
}

/** @file seeLC3.c
 *  @brief Program to demonstrate how to use ISA info from <code>lc3.h</code>
 *  @details Study the code in main to understand how to determine the
 *   number and types of operands a particular LC3 instruction has. This
 *   information is encoded in a data structure defined in <code>lc3.h</code>
 *   This code is a subset of the operations you will need to do when writing
 *   the assembler.
 * <p>
 * @author <b>Fritz Sieker</b>
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "lc3.h"
#include "util.h"

// Some interesting tricks you can do with bit operations
// http://www.catonmat.net/blog/low-level-bit-hacks-you-absolutely-must-know/

// can use ints instead of unsigned ints as long as v is never negative. This
// is true for the use in LC3 assembler.
// see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan

/** Count the number on 1 bits in a value
 *  @param v - the value to use (non-negative)
 * @return - the number of 1 bits
 */
static int count_bits (int v) {
  int c; // c accumulates the total bits set in v
  for (c = 0; v; c++) {
    v &= v - 1; // clear the least significant bit set
  }
  return c;
}

/** print usage statement and exit */

static void usage (void) {
  fprintf(stderr, "Usage: seeLC3 opcode\n");
  fprintf(stderr, "e.g. seeLC3 ADD\n");
  exit(1);
}

/** entry point of program */

int main (int argc, char* argv[]) {
  if (argc != 2)
    usage();

  opcode_t opcode = util_get_opcode(argv[1]);

  if (opcode == OP_INVALID) {
    printf("'%s' is not an opcode\n", argv[1]);
    return -1;
  }

  LC3_inst_t* info = lc3_get_inst_info(opcode); 

  printf("form bit:%2d\n", info->formBit);

  for (int i = 0; i < 2; i++) {
    if (   (info->forms[i].name != NULL)
        && (strcasecmp(argv[1], info->forms[i].name) == 0))  {

      format_t ops    = info->forms[i].operands;
      int      numOps = count_bits(ops);

      printf("form: %d name: %s prototype x%04x %d operand(s):", i,
             info->forms[i].name, info->forms[i].prototype, numOps); 

      if (numOps > 0) {
        for (operand_t opn = OPN_DR; opn <= OPN_FILL; opn <<= 1) {
          if ((ops & opn) != 0)
            printf("'%s' ", lc3_get_operand_name(opn));
        }
      }

      printf("\n");
    }
  }

  return 0;
}

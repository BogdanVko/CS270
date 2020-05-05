/** @file testTokens.c
 *  @brief Simple program to demonstrate how to use the token functions.
 *  @details  This program demonstrates the use of the tokens functions.
 *  Note how the line is tokenized, what is returned and how to iterate over
 *  multiple tokens. What else do you see that may be needed for you to use
 * the functions?
 *  <p>
 *  @author <b>Fritz Sieker</b>
 */
#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

/** print usage statement for program */
static void usage (void) {
  fprintf(stderr, "Usage: testTokens 'line to tokenize' (must include single quotes)\n");
  fprintf(stderr, "e.g. testTokens 'LABEL ADD R1,R2,#5; comment'\n");
  exit (1);
}

/** Simple program to demonstrate how to use the token functions */

int main (int argc, char* argv[]) {
  if (argc != 2)
    usage();

  const char* tok;
  int i = 0;

  tokens_init();

  for (tok = tokenize_lc3_line(argv[1]); tok != NULL; tok = next_token())
    printf("token[%d]: = '%s'\n", i++, tok);

  tokens_term();
  return 0;
}

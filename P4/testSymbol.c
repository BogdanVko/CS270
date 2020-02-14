/*
 * testSsymbol.c - testDriver for the functions of symbol.h
 *
 * "Copyright (c) 2012 by Fritz Sieker."
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
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Debug.h"
#include "symbol.h"

/** @mainpage cs270 Programming Assignment - Symbol Table 
 *  \htmlinclude "symbol.html"
 */

/** @file testSymbol.c
  * @brief Driver to test functions of symbol.c (do not modify)
  *
  * @details This is a driver program to test the functions of symbol.c
  * The program accepts a series of commands and executes those commands one at
  * a time. To understand the usage, type the command <code>help</code>. This
  * will give a brief description of each command and its parameters. Each
  * command and its parameters are on a single line separated by whitespace.
  * <p>
  * @author: Fritz Sieker
  */

/** Maximum length of command line processed */
#define MAX_LINE_LENGTH 128

/** Delimiter used separate tokens on line - used by strtok() */
const char *delim = " \t";

/** Print a usage statement describing how program is used */
static void help() {
  puts("Usage: testSymbol [-debug]\n");
  puts("then enter commands from keyboard, one per line:\n");
  puts("init capacity    - create symbol table with given capacity");
  puts("                     MUST be first action taken");
  puts("add name address - prints 1 on succeses, 0 on failure");
  puts("count            - prints count of names/addresses");
  puts("                     uses function pointers");
  puts("debug level      - turn debug on/off (0 is off)");
  puts("exit/quit        - terminates program");
  puts("get name         - prints NULL or name/address");
  puts("label address    - prints NULL or name associated with address");
  puts("list             - prints all names/addresses");
  puts("                     uses function pointers");
  puts("order option     - calls symbol_order and print value(s)");
  puts("                 - option is HASH|NAME|ADDR");
  puts("search name      - prints NULL or name/address and hash/index");
  puts("size             - call symbol_size()");
  puts("reset            - call symbol_reset()\n");
}

/** Print a usage statement describing how program is used, and exits */
static void usage() {
  help();
}

/** get the next token from the input
 *  @return the token, or exit with error
 */
static char* nextToken () {
  char* tok = strtok(NULL, delim);
  if (! tok)
    usage();
  return tok;
}

/** Get an integer from the input
 *  @return the value, or exit with error
 */
static int nextInt() {
  char* junk;
  char* tok = nextToken();
  return (int) strtol(tok, &junk, 0);
}

/** Example of a call back function called via symbol_iterate()
 */
static void countSymbols (symbol_t* sym, void *data) {
  int* ip = (int*) data;
  *ip = *ip + 1;
}

/** Another example of a call back function called via symbol_iterate()
 */
static void printResult(symbol_t* sym, void* data) {
  FILE* f = (FILE*) data;

  if (! sym)
    fprintf(f, "NULL\n");
  else
    fprintf(f, "name:%-20s addr:%-6d\n", sym->name, sym->addr);
}

/** Test the <code>symbol_order()</code> function */
static void printList (sym_table_t* symTab, int order) {
  int        size = symbol_size(symTab);
  symbol_t** list = symbol_order(symTab, order);

  if (list) {
    for (int i = 0; i < size; i++)
      printResult(list[i], stdout);

    puts("");
    free(list);
  }
}

/** Entry point of the program
 * @param argc count of arguments, will always be at least 1
 * @param argv array of parameters to program argv[0] is the name of
 * the program, so additional parameters will begin at index 1.
 * @return 0 the Linux convention for success.
 */
int main (int argc, const char* argv[]) {
  char line[MAX_LINE_LENGTH];
  int  count, addr;
  char *cmd, *name;
  sym_table_t* symTab = NULL;

  debugInit(&argc, argv);

  if (argc != 1)
    usage();

  while (fgets(line, sizeof(line), stdin) != NULL) {
    char *cr = strchr(line ,'\n'); /* get rid of trailing \n, if any */

    if (cr)
      *cr = '\0';

    cmd = strtok(line, delim);

    if ((! cmd) || (*cmd == '#')) // skip blank lines, comments
      continue;

    if (strcmp(cmd, "debug") == 0) {
      debugLevel  = nextInt();
    }
    else if ((strcmp(cmd, "exit") == 0) || (strcmp(cmd, "quit") == 0)) {
      break;
    }
    else if (strcmp(cmd, "help") == 0) {
      help();
    }
    else if (strcmp(cmd, "init") == 0) {
      count  = nextInt();
      symTab = symbol_init(count);
      debug("initialized with size %d", count);
    }
    else if (symTab == NULL) {
      puts("Please initialize symbol table before use");
    }
    else if (strcmp(cmd, "add") == 0) {
      name = nextToken();
      addr = nextInt();
      printf("%s\n", (symbol_add(symTab, name, addr) ? "OK" : "Duplicate"));
    }
    else if (strcmp(cmd, "count") == 0) {
      count = 0;
      symbol_iterate(symTab, countSymbols, &count);
      printf("symbol count: %d\n", count);
    }
    else if (strcmp(cmd, "get") == 0) {
      name = nextToken();
      printResult(symbol_find_by_name(symTab, name), stdout);
    }
    else if (strcmp(cmd, "label") == 0) {
      addr = nextInt();
      printf("label at addr %d '%s'\n", addr,
             symbol_find_by_addr(symTab, addr));
    }
    else if (strcmp(cmd, "list") == 0) {
      symbol_iterate(symTab, printResult, stdout);
      puts("");
    }
    else if (strcmp(cmd, "order") == 0) {
      name = nextToken();
      if (strcmp(name, "HASH") == 0)
        printList(symTab, HASH);
      else if (strcmp(name, "NAME") == 0)
        printList(symTab, NAME);
      else if (strcmp(name, "ADDR") == 0)
        printList(symTab, ADDR);
      else
        help();
    }
    else if (strcmp(cmd, "reset") == 0) {
      symbol_reset(symTab);
    }
    else if (strcmp(cmd, "search") == 0) {
      int hash, index;
      name              = nextToken();
      struct node* node = symbol_search(symTab, name, &hash, &index);
      printf("symbol '%s' hash: %d index: %d is %s in symbol table\n", name,
             hash, index, (node ? "" : "NOT"));
    }
    else if (strcmp(cmd, "size") == 0) {
      printf("symbol table contains %d entries\n", symbol_size(symTab));
    }
    else {
      help();
    }
  }

  symbol_term(symTab); /* can check for memory leaks now */

  return 0;
}

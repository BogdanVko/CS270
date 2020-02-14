#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author Bogdan Vasilchenko
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16) // 16 bit

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int capacity) {
  sym_table_t *t = malloc(sizeof(sym_table_t));
  t->capacity = capacity;

  t->hash_table = calloc(capacity,sizeof(node_t*));
  t->addr_table = calloc(2^16, sizeof(char*));

  return &t;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
  free(symTab->hash_table);
  free(symTab->addr_table);
  free(*symTab);
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
  return 0;
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  *hash = symbol_hash(name);
  return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
  return NULL;
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  return NULL;
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return 0;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  // symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this

  return 0;
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
  return 0;
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  // will call qsort with either compare_names or compare_addresses
  return NULL;
}


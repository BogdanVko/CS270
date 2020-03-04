#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"
/** NOTE: This shit fucks one up stronger than 2 bottles of Vodka**/
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
  sym_table_t *t = (sym_table_t*) calloc(1,sizeof(sym_table_t));
  t->capacity = capacity;

  t->hash_table = (node_t**) calloc(capacity,sizeof(node_t*));
  t->addr_table = (char**) calloc(LC3_MEMORY_SIZE, sizeof(char*));

  return t;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
  //symbol_reset(symTab);
  
  free(symTab->hash_table);
  
  free(symTab->addr_table);

  free(symTab);
}


void symbol_reset(sym_table_t* symTab) {
  int capacity = symTab->capacity;
  symTab->size = 0;
	free(symTab->hash_table);
  free(symTab->addr_table);

  symTab->hash_table = (node_t**) calloc(capacity,sizeof(node_t*));
  symTab->addr_table = (char**) calloc(LC3_MEMORY_SIZE, sizeof(char*));
	
	

}


/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
  int x = symbol_hash(name);
  int *hash;
  hash = &x;
  int y = (*hash % symTab->capacity);
  int *index;
  index = &y;
  //int *index = &y;

  node_t *searched_node = symbol_search(symTab, name, hash, index);
  
  //  symbol_search(sym_table_t* symTab, const char* name, int* hash, int* index) 
  if (searched_node != NULL)
  {
      return 0;
  }
  
  // So it's not there; Cool
  symTab->size++; //increase the size of symTab by 1
  node_t* new_node = (node_t*) malloc(sizeof(node_t)); 
  new_node->hash = symbol_hash(name); 

	new_node->symbol.addr = addr;
	new_node->symbol.name = strdup(name); 


	new_node->next = symTab->hash_table[*index];
	symTab->hash_table[*index] = new_node;	//link 


  debug("size + 1. Size is%d\n", symTab->size);
  
  
		
	if (symTab->addr_table[addr] == NULL){ 		
			symTab->addr_table[addr] = strdup(name); 
		}

  return 1;
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  
  *hash = symbol_hash(name);
  *index = *hash % symTab->capacity;
  node_t *slot = (symTab->hash_table[*index]); // AM I NOT CLEARING THIS OUT??
  //debug("Recieved a node %s with a hash %d\n", slot->symbol.name, slot->hash);
  debug("echo\n");

  while(slot != NULL){ 
    debug("while loop\n");
		if(*hash == slot->hash){
      debug("hashes are equal\n");
		  char *real_name = strdup(name); 
      
		  char *slots_name = strdup(slot->symbol.name); 
      
			if(*real_name == *slots_name) { //the problem 
        debug("equal names! should return slot, not null");
        return slot;
      }

				 
		}
slot = slot->next; ///Update to next. Treaverse in the list
	}

	return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
  int x = symbol_hash(name);
  int *hash;
  hash = &x;
  int y = (*hash % symTab->capacity);
  int *index;
  index = &y;
  //int *index = &y;

  node_t *searched_node = symbol_search(symTab, name, hash, index);
  if(searched_node != NULL){
    symbol_t* sym = &searched_node->symbol; 
    return sym;

  }
  else {
    return NULL;
  }
}

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  if (symTab->addr_table[addr] != NULL)
  {
    return  symTab->addr_table[addr];
}
  
  
   return NULL;
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {


  for(int i = 0; i < symTab->capacity; i++){    
		node_t* curr = symTab->hash_table[i];   
		
		while(curr != NULL){	    
			(*fnc)(&curr->symbol,data);
			curr=curr->next;
		}
	}
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return symTab->size;
}

char *strlwr(char *str)
{
  char *p = str;

  while (*p) {
     *p = tolower((char)*p);
      p++;
  }

  return str;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
   symbol_t* sym1 = *((symbol_t**) vp1);
   symbol_t* sym2 = *((symbol_t**) vp2);
    /// declared 



   char* str1 = (sym1->name);
   char* str2 = (sym2->name);
   int result = strcasecmp(str1, str2);
    
   return result;
}
 
/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
  symbol_t* sym1 = *((symbol_t**) vp1);
  symbol_t* sym2 = *((symbol_t**) vp2);






  int diff = (sym1->addr) - (sym2->addr);


  if(diff != 0)
    return diff;
  else
    return compare_names(&sym1, &sym2);
}


/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  symbol_t** syms = (symbol_t**)calloc(symTab->size, sizeof(symbol_t*));



  int ind = 0;
  for(int i = 0; i < symTab->capacity; i++){
      node_t* node = symTab->hash_table[i];
      if(symTab->hash_table[i] == NULL)
        continue;
      while(node != NULL){
          syms[ind] = &(node->symbol);
          ind += 1;
          if(node->next == NULL)
            break;
          else
          node = node->next;
      }
        
    }

  if(order == HASH && syms[0] != NULL)
      return syms;
  else if(order == NAME && syms[0] != NULL){
      qsort(syms, symTab->size, sizeof(symbol_t*), compare_names);
      return syms;
  }
  else if(order == ADDR && syms[0] != NULL){
      qsort(syms, symTab->size, sizeof(symbol_t*), compare_addresses);
      return syms;
  }
  else
        return NULL;

  return NULL;

}


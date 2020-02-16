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
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

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
  char**   addr_table;  /**< look up symbols by addr (optional)          */
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

sym_table_t* symbol_init (int capacity) {

	//given- create symTab pointer, allocate
	sym_table_t* symTab=calloc(1,sizeof(sym_table_t));
	//access the member, capacity, and initialize it to int capacity that was passed in
	symTab->capacity = capacity;
	//access the member size, initialize to zero
	symTab->size = 0;
	//allocate and initialize hash_table
	//access member hash_tab and allocate capacity(length of object) by size of elements
	symTab->hash_table=calloc(capacity, sizeof(node_t*));
	//allocate and initialize addr_table[]
	//access member addr_tab and allocate length by size of elements
	symTab->addr_table = calloc(LC3_MEMORY_SIZE,sizeof(char*));
	//return pointer to symTab (symbol table)
  return symTab;
}

//-------------------1----------------------------
void symbol_term (sym_table_t* symTab) {
//Remove all symbols from the symbol table, and 
//!!!free all allocated memory.
	
	
}

//------------------2--------------------------------
/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
//Remove all the symbols from the symbol table.
//call symbol term
	//symbol_term(symTab);
	node_t* nodePtr; //initialize nodePtr
//free symbol.name as well
//set size to 0 at end
//make good
	int j;
	nodePtr = symTab->hash_table[j];
	printf("capacity is %d\n", symTab->capacity);
	for( j = 0; j <= symTab->capacity; j++){ 
		debug("j is %d\n", j);  
		if(symTab->hash_table != NULL){   
			symTab->hash_table[j]->next = NULL;
			//symTab->hash_table[j]->hash = NULL;	//hash value of new node equals 
			//symTab->hash_table[j]->symbol.addr = NULL;	//set addr member to addr
			symTab->hash_table[j]->symbol.name = NULL;	//set that new node name equal to name
		}
	}
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
//Add a symbol to the symbol table
		int hashValue;     //new_node = symTab->hash_table[thisIndex];//set new node to the index of hash table
		node_t* nodePtr; //initialize nodePtr
		int index; //initialize index
		nodePtr = symbol_search(symTab, name, &hashValue, &index); //call symbol_search
		int thisIndex = index; //set index as an int
		//NULL means there is not symbol associated with that name
		//or returns nodes info
		if(nodePtr != NULL){ //if NULL is not returned (a node already exists)
			return 0; //return 0
		}
		else{ //if null is returned, then it doesn't exist yet, so create a new node, put on LL
		node_t* new_node = (node_t*) malloc(sizeof(node_t));  //create/allocate
		//-----set new values of node just created-----
		new_node->symbol.addr = addr;	//set addr member to addr
		new_node->symbol.name = strdup(name);	//set that new node name equal to name
		new_node->hash = symbol_hash(name);	//hash value of new node equals 
		//-----START INSERTION INTO LINKED LIST-----
		new_node->next = symTab->hash_table[thisIndex];	//set next ptr to current value at index (set the next to current head)
		symTab->hash_table[thisIndex] = new_node;	//set current pointer in hash table to the new node we created
		if (symTab->addr_table[addr] == NULL){ 		//if addr value of addr table is null
			symTab->addr_table[addr] =strdup(name); //put name in the addr table
		}
		symTab->size++; //increase the size of symTab by 1
  return 1;
}
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
	*hash = symbol_hash(name); //get hash value ptr
	int capacity = symTab->capacity; //get capacity (for index value)
	*index = *hash % capacity;	//get index value ptr
	node_t* nodePtr; //node ptr
	nodePtr = symTab->hash_table[*index]; //node ptr equal to ptr at index of hash table



	
	while(nodePtr != NULL){ //while the nodePtr is pointing to something
		if(*hash == nodePtr->hash){ //if hash value is equal to hash value of Ptr
			char *actuallName = strdup(name); //get name passed in
			char *testName = strdup(nodePtr->symbol.name); //get name from our nodePtr
			if(actuallName == testName){ //if those names are the same
				return nodePtr; //return our nodes info
			}
		}
		nodePtr = nodePtr->next;
	}
	return NULL;
}

//----------------------------3-------------------------
/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
//Find a symbol by its name
	int hashValue, index;     //new_node = symTab->hash_table[thisIndex];//set new node to the index of hash table
	node_t* nodePtr; //initialize nodePtr
	nodePtr = symbol_search(symTab, name, &hashValue, &index); //call symbol_search
	printf("got this far1\n");
	if(nodePtr != NULL){
		printf("Name found\n");
		return &(nodePtr->symbol);
	}
	printf("didnt go into loop bruh");
  return NULL;
}

//------------------------------4--------------------------	
/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
//Find a name by its LC3 address
  return NULL;
}


/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
	for(int j = 0; j < symTab->capacity; j++){    
		node_t* addr = symTab->hash_table[j];   
		//debug("j is %d\n", j); 
		while(addr != NULL){	    
			(*fnc)(&addr->symbol,data);
			addr=addr->next;
		}
	}
}

//-----------------------------5--------------------------
/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
	return symTab->size;
  //return 0;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  // symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
//symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
//symbol_t* sym2 = *((symbol_t**) vp1); // study qsort to understand this
//symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this

  return 0; //strcasecmp;
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


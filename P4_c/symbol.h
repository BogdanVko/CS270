#ifndef __SYMBOL_H__
#define __SYMBOL_H__


/** @file symbol.h
 *  @brief Defines the interface to symbol.c functions (do not modify)
 *  @details This file defines the interface to a C file symbol.c that
 *  you will complete. The underlying data structure(s) used will be
 *  defined by the actual assignment. The assignment will define whether symbols
 *  are case sensitive or case in-sensitive.
 *  <p>
 *  In this implementation, you will learn about dynamic memory management using
 *  malloc/free. You will also learn about function pointers (callback functions).
 */

/** order in list is order in hash table */
#define HASH  0

/** order in list is alphabetical by name */
#define NAME 1

/** order in list is by increasing address */
#define ADDR 2

/** This defines an opaque type. The actual contents of the structure are hidden
 *  in the implementation (symbol.c) and only a pointer to this structure is
 *  used externally to that file. A pointer to an opaque structure is sometimes
 *  referred to as a handle.
 */

typedef struct sym_table sym_table_t;

/** The symbol_find methods return a pointer to this data structure. It is up
 *  to the implementor to decide how to use this stucture in the implementation.
 */

typedef struct symbol {
    char* name; /**< the name of the symbol */
    int   addr; /**< symbol's address in the LC3 memory */
} symbol_t;

/** Add a symbol to the symbol table. If symbol already exists do nothing and
 *  return 0 (even if associated address is different). If the address has been used
 *  but the symbol doesn't exist add the symbol normally and update the 
 *  char pointer in the addr_table to point at the newly added symbols name.
 *  @param symTab - pointer to the symbol table
 *  @param name - the name of the symbol
 *  @param addr - the address of the symbol
 *  @return 1 if name is NOT in the symbol table,
 *  0 otherwise
 */
int symbol_add (sym_table_t* symTab, const char* name, int addr);

/** Find a name by its LC3 address, use must use the addr_table to perform
 *  the lookup.
 *  @param symTab - pointer to the symbol table
 *  @param addr - an LC3 address
 *  @return the <b>label</b> at that address or NULL if no symbol is
 *  associated with the adddress. 
 */
char* symbol_find_by_addr (sym_table_t* symTab, int addr);

/** Find a symbol by its name
 *  @param symTab - pointer to the symbol table
 *  @param name - the symbols name
 *  @return  the symbols information or NULL if no symbol is associated with
 *   the name.
 *  Most of the work is done by <code>symbol_search()</code>. That routine
 *  returns a <code>node_t*</code>, but this routine returns a 
 *  <code>symbol_t*</code>. Study
 *  <a href="http://stackoverflow.com/questions/5767973/getting-the-address-of-a-struct-member">this</a> posting to understand how you might solve this.
 */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name);

/** Create a new symbol table and return a pointer to it. This function is a
 *  constructor for a symbol table. It allocates and initializes both the
 *  <code>hash_table</code> and the <code>addr_table</code>. The latter is
 *  an array of <code>char*</code> that is indexed by an LC3
 *  address to find the label (if any) associated with that address. 
 *  @param capacity - the size of the hash table. 
 *  @return a pointer to the symbol table.
 */ 
sym_table_t* symbol_init (int capacity);

/** Remove all the symbols from the symbol table. After this call the opaque
 *  symbol table pointer is still valid and new symbols may be added to it. 
 *  If needed, clear the <code>addr_table</code>.
 *  @param symTab - pointer to the symbol table
 */
void symbol_reset (sym_table_t* symTab);

/** This function is only used internally and should be declared static. It is
 *  a useful support function for the <code>add()/find()</code> functions.
 *  It is declared here for documentation purposes. The function returns
 *  <b>three</b> values: one in the return value, and the other two using
 *  the pointers to the hash and index values.
 *  @param symTab - pointer to the symbol table
 *  @param name - the name of the symbol
 *  @param hash - pointer to location where hash value will be stored 
 *  @param index - pointer to location where index will be stored 
 *  @return  the nodes information or NULL if no symbol is associated with
 *   the name.
 */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index);

/** Remove all symbols from the symbol table, and free all allocated memory.
 *  This function is a destructor for a symbol table.
 *  There must not be any memory leaks. After executing this function, the
 *  opaque pointer to the symbol table is no longer valid.
 */
void symbol_term(sym_table_t* symTab);

/** Defines the signature of a callback function (also known as a function
 *  pointer). This is how languages such as Java and C++ do <b>dynamic</b>
 *  binding (i.e. figure out which function to call). Recall that in Java the
 *  code <code>obj.equals(object)</code> will call one of possibly many
 *  different methods depending on the actual type of <code>obj</code>. This
 *  is because the method <b>.equals()</b> may be <b>overridden</b>.
 *  <p>
 *  In the LC3, dynamic binding is based on the <b>JSRR</b> opcode. With this
 *  opcode, the address of the routine to call is stored in a register and can
 *  be changed at runtime. Compare this to a <b>JSR nameOfRoutine</b> opcode which
 *  specifies what routine to call from the label that follows it. Thus, the
 *  address is fixed at <b>assembly</b> time. 
 *  <p>
 *  This is used in the symbol_iterate() function. An interesting variation
 *  would be to have the callback function return an integer which determines
 *  whether the iteration should contibue or terminate.
 *  @param symTab - pointer to the symbol table
 *  @param data - any additional information to be passed on to fnc. The called
 *  function will cast this to whatever type was actually passed.
 */
typedef void (*iterate_fnc_t)(symbol_t* sym, void* data);

/** This function calls the function for every entry in the symbol table.
 *  The assigment will define the order in which the entries should be visited.
 *  @param symTab - pointer to the symbol table
 *  @param fnc - the function to be called on every element
 *  @param data - any additional information to be passed on to fnc. The called
 *  function will cast this to whatever type was actually passed.
 */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data);

/** A callback function for <code>qsort</code> to order by name in a case
 *  insensative way.
 *  @param vp1 pointer to first element
 *  @param vp2 pointer to second element
 *  @ return a number representing the correct ordering (neg, 0, pos)
 */
int compare_names (const void* vp1, const void* vp2);

/** A callback function for <code>qsort</code> to order by address
 *  <b>NOTE</b>: If two elements have the same address, then return the result
 *  of comparing by name, so that name becomes the secondary sort key.
 *  @param vp1 pointer to first element
 *  @param vp2 pointer to second element
 *  @ return a number representing the correct ordering (neg, 0, pos)
 */
int compare_addresses (const void* vp1, const void* vp2);

/** Return the number of elements currently in the symbol table
 *  @param symTab - pointer to the symbol table
 *  @return number of elements
 */
int symbol_size (sym_table_t* symTab);

/** This function returns an ordered, dymanically allocated array of
 *  <code>symbol_t*</code>. You may wish to use <code>qsort()</code> to order
 *  it. The caller will <code>free()</code> the return value.
 *  @param symTab - pointer to the symbol table
 *  @param order - defines the sorting order for the list (HASH, NAME, ADDR)
 *  @return pointer to an array of <code>symbol_t*</code>  
 */ 
symbol_t** symbol_order (sym_table_t* symTab, int order);

#endif /* __SYMBOL_H__ */


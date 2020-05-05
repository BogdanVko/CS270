#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/*
 * "Copyright (c) 2014-2017 by Fritz Sieker."
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
#define NONE  0

/** order in list is alphabetical by name */
#define NAME 1

/** order in list is by increasing address */
#define ADDR 2

/** This defines an opaque type. The actual contents of the structure are hidden
 *  in the implementation (file symbol.c) and only a pointer to this structure
 *  is used externally to this file. A pointer to an opaque structure is
 *  sometimes referred to as a handle.
 */

typedef struct sym_table sym_table_t;

/** The symbol_find methods return a pointer to this data structure. It is up
 *  to the implementor to decide how to use this stucture in the implementation.
 */

typedef struct symbol {
    char* name; /**< the name of the symbol */
    int   addr; /**< symbol's address in the LC3 memory */
} symbol_t;

/** Add a symbol to the symbol table. The names <b>must</b> be unique, but
 *  addresses may be duplicated
 *  @param symTab - pointer to the symbol table
 *  @param name - the name of the symbol
 *  @param addr - the address of the symbol
 *  @return 1 if the name/address are added to the symbol table, 0 otherwise
 */
int symbol_add (sym_table_t* symTab, const char* name, int addr);

/** Find a name by its LC3 address
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
 *  @param hash_capacity - the size of the hash table.
 *  @return a pointer to the symbol table.
 */ 
sym_table_t* symbol_init (int hash_capacity);

/** Remove all the symbols from the symbol table. After this call the
 *  symbol table pointer is still valid and new symbols may be added to it. 
 *  The state of the symbol table after this call is exactly what it was after
 *  <code>symbol_init()</code> was called.
 *  @param symTab - pointer to the symbol table
 */
void symbol_reset (sym_table_t* symTab);

/** Reset the capacity of the hash-table and redistribute the contents to the
 *  new table. After rehashing it is likely that symbols that shared the same
 *  bucket will no longer do so. If a hash table becomes "too" full, it may no
 *  longer provide O(1) lookup. By increasing the size of the underying array,
 *  the performance of lookup may be restored. 
 *  @param symTab - pointer to the symbol table
 *  @param newCapacity - the new capacity of the hash-table
 */
void symbol_rehash (sym_table_t* symTab, int newCapacity);

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
 *  be changed at runtime. Compare this to a <b>JSR nameOfRoutine</b> opcode
 *  which specifies what routine to call from the label that follows it. Thus,
 *  the address is fixed at <b>assembly</b> time. 
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

/** Remove a symbol from the symbol table.
 *  @param symTab - pointer to the symbol table
 *  @param name - the name of the symbol
 *  @return 1 if the symbol was removed, 0 otherwise (name not in symbol table)
 */
int symbol_remove (sym_table_t* symTab, const char* name);

/** Remove all entries from symbol table that have addresses in the given range.
 *  @param symTab - pointer to the symbol table
 *  @param addr1 - lowest address of range
 *  @param addr2 - highest address of range
 */
void symbol_remove_by_addr (sym_table_t* symTab, int addr1, int addr2);

/** This function returns an ordered, NULL terminated, dymanically allocated
 *  array of <code>symbol_t*</code>. Just as a <code>char*</code> (C's string)
 *  is an array of characters terminated with a 0, this function return an
 *  array of <code>symbol_t*</code>, terminated by NULL. You will use
 *  <code>qsort()</code> to sort it. The caller will <code>free()</code> the
 *  return value.
 *  <b>NOTE</b>: This function does not change the underlying symbol table in
 *  any manner.
 *  @param symTab - pointer to the symbol table
 *  @param order - defines the sorting order for the list (HASH, NAME, ADDR)
 *  @return pointer to an array of <code>symbol_t*</code>
 */
symbol_t** symbol_order (sym_table_t* symTab, int order);

#endif /* __SYMBOL_H__ */


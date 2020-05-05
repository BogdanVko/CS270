#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

/*
 * "Copyright (c) 2015-16 by Fritz Sieker."
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

/** @file assembler.h
 *  @brief Defines the interface to assembler.c functions (do not modify)
 *  @details This file defines the interface to a C file assembler.c that
 *  you will complete. This is the main portion of an assembler for LC3.
 *  <p>
 *  This is a substantial assignment. One way to attack larger projects is to
 *  break the problem into pieces and code those pieces individually. You
 *  have already done this for the files <code>util.c</code> and
 *  <code>symbol.c</code>. Instead of writing large functions
 *  (e.g. <code>asm_pass_one(), asm_pass_two()</code>),
 *  decompose them into a series of calls to shorter functions which do
 *  required subtasks. The decomposition may be continued until each low level
 *  function is easy to write correctly. If you find any one function getting
 *  "too" large, think about what the code does and decompose it into several
 *  smaller functions. In fact, if you can give the task a good symbolic name,
 *  you can postpone writing it until later. This is because the name
 *  implies "what" the function does. "How" it is done, will be determined when
 *  that function is coded. It is perfectly fine to have functions that are only
 *  called once from the code. The idea is that each of these functions 
 *  peform a straight forward subtask. And it is perfectly fine to have
 *  functions that are only one or a few lines of code.
 *  <p>
 *  A good rule of thumb is that a function is too large if you can not see the
 *  entire function on a single page.
 *  <p>
 *  @author Fritz Sieker
 */

#include <stdbool.h>

#include "lc3.h"
#include "symbol.h"

/** Handy way of defining global variable in a header file */
#ifndef LC3AS_VAR
#define LC3AS_VAR extern
#endif

/** Error messages passed to function <code>asm_error()</code> */
#define ERR_OPEN_READ       "could not open '%s' for reading."
#define ERR_OPEN_WRITE      "could not open '%s' for writing."
#define ERR_LINE_TOO_LONG   "source line too long (max is %d)"
#define ERR_NO_ORIG         "no .ORIG directive found"
#define ERR_MULTIPLE_ORIG   "multiple .ORIG found"
#define ERR_NO_END          "no .END directive found"
#define ERR_ORIG_NOT_1ST    "instruction(s) appear before .ORIG"
#define ERR_END_NOT_LAST    "instruction(s) appear after .END - ignored"
#define ERR_EXPECTED_COMMA  "expected comma, got '%s'"
#define ERR_EXPECTED_REG    "expected register (R0-R7), got '%s'"
#define ERR_EXPECT_REG_IMM  "expected register or immediate, got '%s'"
#define ERR_BAD_LABEL       "label '%s' contains illegal characters"
#define ERR_MISSING_OP      "expected LC3 op, got '%s'"
#define ERR_MISSING_OPERAND "too few operand(s)"
#define ERR_EXTRA_OPERAND   "extra operand(s) '%s'"
#define ERR_DUPLICATE_LABEL "label '%s' previously defined"
#define ERR_MISSING_LABEL   "label '%s' never defined"
#define ERR_BAD_PCOFFSET    "PCoffset to '%s' out of range"
#define ERR_BAD_IMM         "immediate '%s' (bad format)"
#define ERR_IMM_TOO_BIG     "immediate '%s' out of range"
#define ERR_EXPECTED_STR    "expected quoted string, got '%s'"
#define ERR_BAD_STR         "unterminated string '%s'"
#define ERR_EXPECTED_FILL   "expected .FILL value, got '%s'"
#define ERR_BAD_CHAR_CONST  "incorrect character constant \"%s\""

/** A global variable defining the number of errors found */
LC3AS_VAR int numErrors;

/** A global variable defining whether to print pass1 info */
LC3AS_VAR int printPass1;

/** Typedef of structure type */
typedef struct line_info line_info_t;

/** Structure containing all the values that might be found in a source line.
 *  The contents of this structure are set during <code>pass_one()</code> and
 *  used to build the 16 bit instruction during <code>pass_two</code>. This
 *  is only used in <code>assembler.c</code>, but is declared here for
 *  documentation purposes.
 */
struct line_info {
  line_info_t*   next;         /**< Allow for linked list                   */
  int            lineNum;      /**< Line number in source code              */
  int            address;      /**< LC3 address of instruction              */
  opcode_t       opcode;       /**< opcode of instruction      (bits 15..13)*/
  inst_format_t* format;       /**< name/operands/prototype for instruction */
  int            DR;           /**< DR or SR, if present       (bits 11..9) */
  int            SR1;          /**< SR1 or BaseR, if present   (bits  8..6) */
  int            SR2;          /**< SR2, if present            (bits  2..0) */
  int            immediate;    /**< Immediate value, if present             */
  char*          reference;    /**< Label referenced by instruction, if any */
};

/** A function to print error messages. This function takes a minimum of one
 *  parameter. It is exaclty like the <code>printf()</code> function. The first
 *  parameter is a formatting string. This will be one of the values defined
 *  above that starts with <code>ERR_</code>.The remaining parameters (if any)
 *  are the actual values to be printed (generally a token). The function
 *  prints the word <code>ERROR:</code> and the the value of <code>srcLineNum</code>
 *  along with the information provided by the parameters. It <b>must</b> be
 *  used for reporting all errors. After printing the error, the global
 *  variable <code>numErrors</code> is incremented. This function relies on the
 *  static variable <code>srcLineNum</code> in <code>assembler.c</code>.
 *  Suppose one wanted to report that a file could not be opened for reading.
 *  The C code might look line this.
 *  <pre></code>
 *  FIlE* f = fopen(filename, "r");
 *  if (f == NULL) {
 *    asm_error(ERR_OPEN_READ, filename);
 *    // any other actions 
 *  }
 *  </code></pre>
 *  Ideally, this function would throw an exception.
 *  @param msg - the formating string (one of the <code>ERR_xxx</code> macros)
 *  @param ... - a list of values to be substitued into the format string.
 */
void asm_error (const char* msg, ...);

/** A function to initialize all the fields of the structure to default values.
 *  Since C does not have constructors, it is convenient to write functions to
 *  initialize fields of a structure to default values. The first parameter
 *  allows the function to be used in two ways. If its value is
 *  <code>NULL</code>, the structure is <code>malloc()</code>-ed. If it is not
 *  <code>NULL</code>, the structure pointed to by the parameter is initialized.
 *  This allow the easy initialization of a local variabe in some other
 *  function by passing its address. The fields <code>info->lineNum</code> and
 *  <code>info->address</code> are initialized from global values defined in
 *  <code>assembler.c</code>. You <b>may</b> modify this function to do
 *  additional checks and initialization if you find that usefull. You <b>may
 *  not</b> change its signature. This function is only used in
 *  <code>assembler.c</code> and should be <code>static</code>. It is declared
 *  here for documentation purposes.
 *  @param info pointer to an existing structure or <code>NULL</code>
 *  @param opTok the string representing the operation (e.g. <code>"ADD"</code>
 *  @return a pointer to the initialized structure
 */
line_info_t* asm_init_line_info (line_info_t* info, const char* opTok);

/** A function to print the infomation extracted from a source line. This is
 *  used for debugging only.
 *  @param info - pointer to informaton about a source line
 */
void asm_print_line_info (line_info_t* info);

/** Do whatever initialization is necessary for the assembler */
void asm_init (void);

/** This function performs the processing required in the first pass. At a
 *  minimum, it must check the syntax of each instruction and create the symbol
 *  table. For this assignment, it will also create a linked list for use
 *  by the second pass. The flow of this function is:
 *  <ol>
 *  <li>open the source file and report any error</li>
 *  <li>read the lines one at a time using <code>fgets()</code></li>
 *  <li>convert the line to a list of tokens</li>
 *  <li>if there is a label in the line, add it to the symbol table</li>
 *  <li>if there is an opcode (e.g. <code>ADD</code>) on the line, then</li>
 *  <ol>
 *     <li>allocate/initialize a new <code>line_info_t</code> structure</li>
 *     <li>convert the tokens to values and set the appropriate fields
 *         of the structure</li>
 *     <li>add the structure to the tail of the linked list</li>
 *     <li>update the current address</li>
 *  </ol>
 *  <li>If there were no errors, write the symbol table file using
 *      <code>lc3_write_sym_tab()</code>.</li>
 *      </li>
    <li>return the linked list</li>
 *  </ol>
 *  @param asm_file_name - name of the <code>.asm</code> file to assemble
 *  @param sym_file_name - name of the symbol table file
 *  @return - a linked list of information about each source line
 */
line_info_t* asm_pass_one (const char* asm_file_name, const char* sym_file_name);

/** This function generates the object file. It is only called if no errors were
 *  found during <code>asm_pass_one()</code>. The basic structure of this code
 *  is to loop over the data structure created in <code>asm_pass_one()</code>,
 *  generate object code (16 bit LC3 instructions) and write it to the object
 *  file using <code>lc3_write_LC3_word()</code>. The function also
 *  calculates the <code>PCoffset</code> and verify that they are within range.
 *  Use the following formula for calculation:<pre><code>
 *  targetAddress = instructionAddress + 1 + PCoffset
 *  </code></pre>
 *  The <code>targetAddress</code> is found by looking up the <code>reference</code>
 *  in the symbol table. The <code>instructionAddress</code> is in the
 *  <code>line_info_t</code> structure. <b>Note</b> that the
 *  <code>PCoffset</code> only uses a subset of the bits in an <code>LC3</code>
 *  instruction.
 *  @param obj_file_name - name of the object file for this source code
 *  @param list - the linked list produced by <code>asm_pass_one()</code>
 */
void asm_pass_two(const char* obj_file_name, line_info_t* list);

/** Cleanup everything used by the assembler. 
 *  @param list - the list produced by <code>asm_pass_one()</code>
 */
void asm_term (line_info_t* list);

#endif

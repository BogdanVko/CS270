#ifndef __LC3_H__
#define __LC3_H__

/*
 * "Copyright (c) 2014-2015 by Fritz Sieker."
 * based on ideas/code by Steven S. Lumetta
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

/** @file lc3.h
 *  @brief definitions of the LC3 instruction set architecture (ISA) (do not modify)
 *  @details This defines the details of the LC3 instruction set architecture
 *  (ISA). It is a separate file so that it can be shared by both an assembler
 *  and a simulator. It also include various utility routines.
 * <p>
 * @author Fritz Sieker
 */

#include <stdio.h>
#include <stdbool.h>

#include "symbol.h" 

/** Handy way to define a gloabal variable in header file */
#ifndef LC3_VAR
#define LC3_VAR extern
#endif

/** Prototype for handy function to duplicate a string. This function allocates
 *  dynamic memory and copies the string into that memory. Thus, use of this
 *  function implies the need to free the string at some point.
 */
char* strdup(const char *);

/** LC3 words are 16 bits */
#define LC3_WORD unsigned short

/** The LC3 defines a memory accessed by a 16 bit address */
#define LC3_MEM_SIZE (1 << 16)

/** The LC3 contains 8 general purpose register, named R0..R7 */
#define LC3_NUM_REGS 8  

/** Return address stored in R7 */
#define RETURN_ADDR_REG   7

/** Size array of buckets in symbol.c (a prime number) */
#define SYM_TAB_SIZE 997

/** The LC3 opcodes and pseudo-ops. The codes of OP_BR .. OP_TRAP corresponds
 *  exactly to the numeric values assigned to the 16 LC3 instructions. The
 *  codes assigned to the pseudo-ops is arbitrary. PCi is the incremented PC
 */
typedef enum opcode {
  OP_INVALID = -1, /**< invalid opcode                                       */
  OP_BR,           /**< PC = PCi + PCoffset9 if condition is met             */
  OP_ADD,          /**< DR = SR1 + SR2 or DR = SR1 + imm5                    */
  OP_LD,           /**< DR = mem[PCi + PCoffset9]                            */
  OP_ST,           /**< mem[PCi + PCoffset9] = SR                            */
  OP_JSR_JSRR,     /**< R7 = PCi and (PC = SR or PC = PCi + PCoffest9)       */
  OP_AND,          /**< DR = SR1 & SR2 or DR = SR1 & imm5                    */
  OP_LDR,          /**< DR = mem[BaseR + offset6]                            */
  OP_STR,          /**< mem[BaseR + offset6] = SR                            */
  OP_RTI,          /**< PC = R7, exit supervisor mode                        */
  OP_NOT,          /**< DR = ~SR1                                            */
  OP_LDI,          /**< DR = mem[mem[PCi + PCoffset9]]                       */
  OP_STI,          /**< mem[mem[PCi + offset9]] = SR                         */
  OP_JMP_RET,      /**< PC = R7 (RET) or PC = Rx (JMP Rx)                    */
  OP_RESERVED,     /**< Currently not used                                   */
  OP_LEA,          /**< DR = PCi + PCoffset9                                 */
  OP_TRAP,         /**< R7 = PCi, PC = mem[mem[trap]], enter supervisor mode */
  OP_ORIG,         /**< memory location where code is loaded                 */
  OP_END,          /**< end of propgram - only comments may follow           */
  OP_BLKW,         /**< allocate N words of storage initialized with 0       */
  OP_FILL,         /**< allocate 1 word of storage initialed with operand    */
  OP_STRINGZ,      /**< allocate N+1 words of storage initialized with
                            string and null terminator (1 char per word)     */
  OP_GETC,         /**< Read character from keyboard, no echo      (trap x20)*/
  OP_OUT,          /**< Write one character                        (trap x21)*/
  OP_PUTS,         /**< Write null terminated string               (trap x22)*/
  OP_IN,           /**< Print prompt and read/echo character       (trap x23)*/
  OP_PUTSP,        /**< Write packed null terminated string        (trap x24)*/
  OP_HALT,         /**< Halt execution                             (trap x25)*/
  OP_GETS,         /**< Read string from keyboard, store in memory (trap x26)*/
  OP_NEWLN,        /**< write newline to output                    (trap x27)*/
  OP_ZERO,         /**< DR = 0 (shorthand for AND DR,DR,#0)                  */
  OP_COPY,         /**< DR = SR1 (shorthand for ADD DR,SR1,#0)               */
  OP_SETCC,        /**< Shorthand for ADD DR,DR,#0 - set cond code from reg  */
  OP_SUB,          /**< reserved for future optional subtract pseudo-op      */
  NUM_OPCODES      /**< Initialized by compiler                              */
} opcode_t;

/** A bit field used to define the types of operands an individual
 *  LC3 instruction may have. Each value represents a different bit in
 *  the final result. When you see C code like this, it is likely that
 *  an integer value is used to represent an "array" of up to 32
 *  values. Each value is accessed with a mask that extracts the bit of
 *  interest. See the inst_format_t below.
 */
typedef enum operand {
    OPN_DR    = 0x0001, /**< DR or SR         (bits 11..9)     */
    OPN_SR1   = 0x0002, /**< SR1 or BaseR     (bits  8..6)     */
    OPN_SR2   = 0x0004, /**< SR2              (bits  2..0)     */
    OPN_CC    = 0x0008, /**< condition codes  (bits 11..9)     */
    OPN_IMM5  = 0x0010, /**< imm5    (signed) (bits  4..0)     */
    OPN_OFF6  = 0x0020, /**< offset6 (signed) (bits  5..0)     */
    OPN_VEC8  = 0x0040, /**< trapvect8        (bits  7..0)     */
    OPN_ASC8  = 0x0080, /**< 8 bit ASCII      (bits  7..0)     */
    OPN_PCO9  = 0x0100, /**< label (or address for PCoffset9)  */
    OPN_PCO11 = 0x0200, /**< label (or address for PCoffset11) */
    OPN_IMM16 = 0x0400, /**< unsigned value for .BLKW/.ORIG    */
    OPN_STR   = 0x0800, /**< operand is string literal         */
    OPN_FILL  = 0x1000  /**< can be a value or label           */
} operand_t;

/** Define a combinatin of operands an opcode may have. For example, the
 *  the LD, LDI, ST and STI instructions all have two parameters. The
 *  first is a register, the second is a nine bit offset. This code stores
 *  multiple values in a single integer value by using individual
 *  bits to encode information. The ordering is right to left, with the
 *  rightmost 1 bit being the type of the first operand.
 *  <p>
 *  To determine the number of operands an instruction has, simply count the
 *  1 bits in the word. <a href="https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan">
 *  Here</a> is an algorithum by Brian Kernigan, one of the developers of Unix,
 *  and co-author of the famous book "The C Programing Language (known as K&R)".
 */
typedef enum format {
  FMT_      = 0,
  FMT_RRR   = (OPN_DR | OPN_SR1 | OPN_SR2),
  FMT_RRI5  = (OPN_DR | OPN_SR1 | OPN_IMM5),
  FMT_CL    = (OPN_CC | OPN_PCO9),
  FMT_R1    = OPN_DR,
  FMT_R2    = OPN_SR1,
  FMT_I11   = OPN_PCO11,
  FMT_RL    = (OPN_DR | OPN_PCO9),
  FMT_RRI6  = (OPN_DR | OPN_SR1 | OPN_OFF6),
  FMT_RR    = (OPN_DR | OPN_SR1),
  FMT_V     = OPN_VEC8,
  FMT_A     = OPN_ASC8,
  FMT_16    = OPN_IMM16,
  FMT_S     = OPN_STR,
  FMT_FILL  = OPN_FILL
} format_t;

/** This structure stores the information for one form of an instruction.
 *  Several instructions have multiple forms, but most have only one.
 */
typedef struct inst_format {
 char*      name;      /**< human readable name (e.g. "ADD")             */
 format_t   operands;  /**< operands for this instruction (e.g. FMT_RRR) */
 int        prototype; /**< bits that are constant in this instruction   */
} inst_format_t;

/** This structure stores the information about a single instruction.
 *  See the usage in lc3.c where the information for each LC3 instruction
 *  is defined. The name of the second form will be <code>NULL</code> unless
 *  the instruction actually has two forms.
 */
typedef struct LC3_inst {
  int           formBit;    /**< -1 if instruction has only one format,
                                 else bit that differentiates format.
                                 This field is <b>only</b> used in the
                                 simulator, where it is used to differentiate
                                 the two ADD/AND formats and the JSR/JSRR */
  inst_format_t forms[2];   /**< syntax for both possible forms. It is possible
                                 to have two forms even when the form bit
                                 has a value of -1. For example JMP/RET are
                                 really the <b>same</b> instruction. RET is
                                 simply a shorthand for JMP R7 */
} LC3_inst_t;

/** Convert an escape sequence to a single character
 *  @param c the character <b>after</b> the escape character (the back-slash)
 *  @return the ascaped value of the character
 */ 
char lc3_escaped_char (char c);

/** Get the information for an instruction, given its opcode This is simply
 *  an access into an array of values initialized with the information for
 *  each of the LC3's sixteen instructions and additional pseudo-ops.
 *  @param opcode - the opcode of the instruction/pseudo-op of interest
 *  @return - a pointer to the syntax information for this instruction or NULL
 */
LC3_inst_t* lc3_get_inst_info (opcode_t opcode);

/** Get the format for an instructon given its name.
 *  The <code>ADD/AND</code> instructions have two forms with the same name
 *  and this routine will return the one with reg,reg,imm5.
 *  @param name the opcode as a string (e.g. <code>"AND"</code>)
 *  @return a pointer to the format or <code>NULL</code>
 */
inst_format_t* lc3_get_inst_format (const char* name);

/** Get the suffix of a file name
 *  @param file_name - file name to check
 *  @return - a pointer to the rightmost location of '.' in file_name or to
 *  the null byte at the end of file_name.
 */
char* lc3_get_suffix (char* file_name);

/** Determine if file_name has the specified suffix
 *  @param file_name - file name to check
 *  @param suffix - value to match
 *  @return - true if suffix matches actual suffix of file_name
 */
bool lc3_file_has_suffix (const char* file_name, const char* suffix);

/** Create a new dynamically allocated string with the existing suffix
 *  (if any) replaced by a new suffix.
 *  @param file_name - original file name
 *  @param new_suffix - replace existing suffix with this value
 *  @return - the new string (must be free'd by caller)
 */
char* lc3_replace_suffix (const char* file_name, char* new_suffix);

/** Convert a format_t to a "name"
 *  @param format - the value to convert (e.g. FMT_RRI5)
 *  @return - a human readable name (e.g. "reg,reg,imm5" )
 */
const char* lc3_get_format_name (format_t format);

/** convert an <code>opcode_t</code> to a name
 *  @param op - the opcode to convert (e.g. OP_ADD)
 *  @return - a human readable name (e.g. "ADD")
 */
const char* lc3_get_opcode_name (opcode_t op);

/** convert operand type to a "name"
 *  @param operand - the type of operand (e.g. OPN_OFF6)
 *  @return a human readable name (e.g. offset6)
 */
const char* lc3_get_operand_name (operand_t operand);

/** Set 'inHex' depending on the file suffix. lc3_read_LC3_word()
 *  and lc3_write_LC3_word() depend on 'inHex'
 *  @param name - the name of the file
 */
void lc3_set_obj_file_mode (const char* name);

/** Read an LC3 word from a file (binary or hex - see lc3_set_obj_file_mode()) 
 *  @param f - the object file
 *  @return the value, or -1 on EOF
 */
int lc3_read_LC3_word (FILE *f);

/** Read the symbol table file and populate the global variable
 *  <code>lc3_sym_tab</code>. No error checking is performed. It is assumbed
 *  the file is in the correct format.
 *  @param sym_file the file containing the symbol table
 *  @param symTab pointer to the symbol table
 */
void lc3_read_sym_table (FILE* sym_file, sym_table_t* symTab);

/** Write an LC3 word to a file (binary or hex - See lc3_set_obj_file_mode())
 *  @param f - the file to write to
 *  @param value - the value to write
 */
void lc3_write_LC3_word (FILE* f, int value);

/** Write the symbol table to a file from the global variable
 *  <code>lc3_sym_tab</code>
 *  @param sym_file - the file in which the symbol table is written
 *  @param symTab - pointer to the symbol table
 */
void lc3_write_sym_table (FILE* sym_file, sym_table_t* symTab);

/** Convert a string to an address. The string is assumed to be a symbol. If
 *  it is found in the symbol table, the address is returned via the pointer.
 *  Otherwise call lc3_get_int() to convert the "number" to an address.
 *  @param symTab - the file in which the symbol table is written
 *  @param token - the string to be converted
 *  @param value - pointer to where the address will be stored
 *  @return true on success, false on failure
 */
bool lc3_get_address (sym_table_t* symTab, const char* token, int* value);

/** Convert a string to an integer using the LC3 syntax for constants.
 *  The LC3 format assumes hex <b>unless</b> the string is preceeded by a
 *  &# sign to indicate decimal values. The initial x/X for hex values is
 *  optional. Hex values may be preceeded by a '-'.
 *  @param token - the string to be converted
 *  @param value - pointer to where value will be stored
 *  @return true on success, false on failure
 */
bool lc3_get_int (const char* token, int* value);

#endif /* __LC3_H__ */


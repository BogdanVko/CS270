#ifndef __DEBUG_H__
#define __DEBUG_H__

/** @file Debug.h
 *  @brief Define a <b>simple</b> debugging interface to use in C programs
 *  @details One method of debugging your C program is to add <tt>printf()</tt>
 *  statements to your code. This file provides a way of including debug
 *  output, and being able to turn it on/off either at compile time or
 *  at runtime, without making <b>any</b> changes to your code.
 *  Two levels of debugging are provided. If the value <tt>DEBUG</tt> is
 *  defined, your debug calls are compiled into your code. Otherwise, they are
 *  removed by the optimizer. There is an additional run time check as to
 *  whether to actually print the debugging output. This is controlled by the
 *  value <tt>debugLevel</tt>.
 *  <p>
 *  To use it with <tt>gcc</tt>, simply write a <tt>printf()</tt> call, but
 *  replace the <tt>printf()</tt> call by <tt>debug()</tt>.
 *  <p>
 *  To easily print the value of a <b>single</b> variable, use
 *  <pre><tt>
    vDebug("format", var); // "format" is the specifier (e.g. "%d" or "%s", etc)
 *  </tt></pre>
 *  <p>
 *  To use debug(), but control when it prints, use
 *  <pre><tt>
    lDebug(level, "format", var); // print when debugLevel >= level
 *  </tt></pre>
 *  <p>
 *  Based on code and ideas found 
 *  <a href="http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing">
 *  here</a> and
 *  <a href="http://stackoverflow.com/questions/679979/how-to-make-a-variadic-macro-variable-number-of-arguments">
 *  here</a>. 
 *  <p>
 *  @author Fritz Sieker
 **/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/** Initialize the variable <tt>debugLevel</tt> depending on the value
 *  of <tt>argv[1]</tt>. Normally called from <tt>main</tt> with the program
 *  arguments. If <tt>argv[1]</tt> is or begins with <tt>-debug</tt>, the
 *  value of <tt>debugLevel</tt> is set and <tt>argc, argv</tt> are
 *  modified appropriately. An entry of <tt>-debug5</tt> sets the level to 5.
 *  If the function is not called, the user is responsible for setting
 *  <tt>debugLevel</tt> in other code.
 *  @param argc the number of command line arguments
 *  @param argv the array of command line arguments.
 */
void debugInit(int* argc, const char* argv[]);

/** Send the debug output to a file
 *  @param fileName name of file to write debug output to
 */
void debugToFile(const char* fileName);

/** Close the external file and reset <tt>debugFile</tt> to <tt>stderr</tt>
 */
void debugClose(void);

/** Control how much debug output is produced. Higher values produce more
 * output. See the use in <tt>lDebug()</tt>.
 */
extern int debugLevel;

/** The file where debug output is written. Defaults to <tt>stderr</tt>.
 *  <tt>debugToFile()</tt> allows output to any file.
 */
extern FILE* debugFile;

#ifdef DEBUG
#define DEBUG_ENABLED 1  // debug code available at runtime
#else
/** This macro controls whether all debugging code is optimized out of the
 *  executable, or is compiled and controlled at runtime by the
 *  <tt>debugLevel</tt> variable. The value (0/1) depends on whether
 *  the macro <tt>DEBUG</tt> is defined during the compile.
 */
#define DEBUG_ENABLED 0  // all debug code optimized out
#endif 

/** Print the file name, line number, function name and "HERE" */
#define HERE debug("HERE")

/** Expand a name into a string and a value
 *  @param name name of variable
 */
#define debugV(name) #name,(name)

/** Output the name and value of a single variable
 *  @param fmt the formatting string (<b>MUST</b> be a literal)
 *  @param name name of the variable to print
 */
#define vDebug(fmt, name) debug("%s=(" fmt ")" , debugV(name))

/** Simple alias for <tt>lDebug()</tt> */
#define debug(fmt, ...) lDebug(1, fmt, ##__VA_ARGS__)

/** Print this message if the variable <tt>debugLevel</tt> is greater
 *  than or equal to the parameter.
 *  @param level the level at which this information should be printed
 *  @param fmt the formatting string (<b>MUST</b> be a literal)
 */
#define lDebug(level, fmt, ...) \
  do { \
    if (DEBUG_ENABLED && (debugLevel >= level)) \
      fprintf((debugFile ? debugFile : stderr), "DEBUG %s[%d] %s() " fmt "\n", \
               __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
  } while(0)

#ifdef __cplusplus
}
#endif

#endif


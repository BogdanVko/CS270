/*
 * "Copyright (c) 2016 by Fritz Sieker."
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Debug.h"

int debugLevel = 0;

FILE* debugFile = 0;

static const char* prefix = "-debug";

void debugInit (int* argc, const char* argv[]) {
  debugFile = stderr;

  if (*argc > 1) {
    const char* arg1 = argv[1];
    size_t len = strlen(prefix);

    if (strncmp(arg1, prefix, len) == 0) {
      debugLevel = 1;

      if (strlen(arg1) > len)
        debugLevel = atoi(arg1 + len);

      (*argc)--; // decrement number of arguments

      for (int i = 1; i < *argc; i++) // remove first argument
        argv[i] = argv[i+1];
    }
  }
}

void debugToFile (const char* fileName) {
  debugClose();

  FILE* f = fopen(fileName, "w"); // "w+" ?

  if (f)
    debugFile = f;
}

void debugClose(void) {
  if (debugFile && (debugFile != stderr)) {
    fclose(debugFile);
    debugFile = stderr;
  }
}


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


#include "arglist.h"

#include <stddef.h>
#include <stdio.h>

#include "util.h"
#include "stdlib.h"

char* argv[MAXARGC];
char* cmd;
size_t pos;

void pushArg(char* arg) {
    argv[pos++] = strdup(arg);
    argv[pos] = NULL; // set new end to NULL
}

void popArgsFreeStrings(void) {
    size_t i = 0;
    for (i = 0; i < pos; ++i) {
        free(argv[i]);
        argv[i] = NULL;
    }
    pos = 0;

    // now free cmd
    free(cmd);
    cmd = NULL;
}

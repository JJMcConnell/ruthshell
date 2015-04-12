#include "variable.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

VariableEntry vartab[MAXNUMVARS];
size_t varCount;

void addVariable(char* var, char* val) {
    // check if we should replace any
    size_t i = 0;
    for (i = 0; i < varCount; ++i) {
        if (streq(vartab[i].var, var)) {
            //replace
            strcpy(vartab[i].val, val);
            return;
        }
    }

    VariableEntry* e = &vartab[varCount++];
    e->val[0] = '\0';
    e->var[0] = '\0';
    strcpy(e->var, var);
    strcpy(e->val, val);
}

void removeVariable(char* var) {
    size_t i = 0;
    for (i = 0; i < varCount; ++i) {
        if (streq(vartab[i].var, var)) {
            // shift all to the right over left
            size_t j = 0;
            for (j = i + 1; j < varCount; ++j)
                moveVariableLeft(j);

            --varCount;
            return;
        }
    }
}

void moveVariableLeft(size_t i) {
    VariableEntry* e = &vartab[i];
    VariableEntry* eLeft = &vartab[i - 1];

    strcpy(eLeft->var, e->var);
    strcpy(eLeft->val, e->val);
}

void listAllVariables(void) {
    size_t i = 0;
    
    for (i = 0; i < varCount; ++i)
        printf("%s = %s\n", vartab[i].var, vartab[i].val);
}

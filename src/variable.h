#ifndef VARIABLE_H_
#define VARIABLE_H_

#define MAXNUMVARS 200
#define MAXVARLENGTH 200

#include <stddef.h>

typedef struct _variabletable {
    char var[MAXVARLENGTH];
    char val[MAXVARLENGTH];
} VariableEntry;

extern VariableEntry vartab[];
extern size_t varCount;

void addVariable(char* var, char* val);
void removeVariable(char* var);
void moveVariableLeft(size_t i);
void listAllVariables(void);
char* expand(char* var);

#endif /* VARIABLE_H_ */

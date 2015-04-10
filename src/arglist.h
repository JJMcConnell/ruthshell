#ifndef ARGLIST_H_
#define ARGLIST_H_

#include <stddef.h>

#define MAXARGC 256            // max number of args

/* these are used for external commands */
extern char* cmd;
extern char* argv[]; // note: last pointer must be NULL

extern size_t pos;

/* initialize the list */
void initArgv(void);

/* push an arg onto argv */
void pushArg(char* arg);
/* clear out argv and cmd; free all memory */
void popArgsFreeStrings(void);

#endif /* ARGLIST_H_ */

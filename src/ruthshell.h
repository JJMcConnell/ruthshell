#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

#include "alias.h"

/* some definitions */
#define MAXSTRINGLEN 1024
#define EXITSUCCESS 100
#define EOLFOUND    0

/* these should be defined on the unix (POSIX) system */
extern char** environ;
extern int execvpe(const char *file, char *const argv[],
        char *const envp[]);

/* lists */
extern char strBuffer[]; //constness should be different here

/* stores second to last WORD token found */
extern char secondToLastWord[];

/* needed for bison/flex */
void yyerror(const char *str);
int yywrap();

/*** Shell Operations ***/
/* init and teardown */
void init(); // creates lists and such
void teardown(); // deallocate those from above

/* builtins */
int cdHome(void);
int cd(char* path);
int bye(void);
void alias(void);
void aliasAdd(char* name, char* word);
void unalias(char* name);

/* external commands */
int runCmdAndFreeStrings(void);

#endif /* RUTH_SHELL_H */

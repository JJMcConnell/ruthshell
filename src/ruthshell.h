#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* some definitions */
#define MAXSTRINGLEN 1024
#define EXITSUCCESS 100
#define EOLFOUND    0
#define VARNOTFOUND 101

#include <stdbool.h>

/* lists */
extern char lastWord[];

/* stores second to last WORD token found */
extern char secondToLastWord[];

/* stores filde for the right side of the pipe */
extern int fdRight;

extern bool interactive;

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
void ruthSetenv(char* variable, char* word);
void ruthPrintenv(void);
void ruthUnsetenv(char* variable);

/* metacharacters */


/* external commands */
int runCmdAndFreeStrings(void);
int runPipedCmdAndFreeStringsLeft(void);
int runPipedCmdAndFreeStringsRight(void);

#endif /* RUTH_SHELL_H */

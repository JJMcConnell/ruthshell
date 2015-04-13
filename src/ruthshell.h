#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* some definitions */
#define MAXSTRINGLEN 1024
#define EXITSUCCESS 100
#define EOLFOUND    0
#define VARNOTFOUND 101

/* lists */
extern char lastWord[];

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
void ruthSetenv(char* variable, char* word);
void ruthPrintenv(void);
void ruthUnsetenv(char* variable);

/* metacharacters */


/* Signal Handling */
void signal_handler(int signo);


/* external commands */
int runCmdAndFreeStrings(void);

#endif /* RUTH_SHELL_H */

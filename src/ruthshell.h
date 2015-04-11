#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* some definitions */
#define MAXSTRINGLEN 256
#define EXITSUCCESS 100
#define EOLFOUND    0

/* these should be defined on the unix (POSIX) system */
extern char** environ;
extern int execvpe(const char *file, char *const argv[],
        char *const envp[]);


char strBuffer[MAXSTRINGLEN]; //constness should be different here

/* needed for bison/flex */
void yyerror(const char *str);
int yywrap();

/*** Shell Operations ***/
/* builtins */
int cdHome(void);
int cd(char* path);
int bye(void);
int alias(void);
int aliasAdd(char* name, char* word);
int unalias(char* name);

/* external commands */
int runCmdAndFreeStrings(void);

#endif /* RUTH_SHELL_H */

#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* some definitions */
#define MAXSTRINGLEN 256
#define EXITSUCCESS 100
#define EOLFOUND    0

char strBuffer[MAXSTRINGLEN]; //constness should be different here

/* needed for bison/flex */
void yyerror(const char *str);
int yywrap();

/*** Shell Operations ***/
/* builtins */
int cdHome(void);
int cd(char* path);
int bye(void);

/* external commands */
int runcmd(char* command);

#endif /* RUTH_SHELL_H */

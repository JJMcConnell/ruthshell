#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* needed for bison/flex */
void yyerror(const char *str);
int yywrap();

/*** Shell Operations ***/
/* builtins */
int cdHome(void);
int cd(char* path);

/* external commands */
int runcmd(char* command);

#endif /* RUTH_SHELL_H */

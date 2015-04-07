#ifndef RUTH_SHELL_H
#define RUTH_SHELL_H

/* needed for bison/flex */
void yyerror(const char *str);
int yywrap();

int runcmd(char* command);

#endif /* RUTH_SHELL_H */

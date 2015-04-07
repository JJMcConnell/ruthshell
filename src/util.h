#ifndef UTIL_H_
#define UTIL_H_

/*** Utils ***/
void printPrompt(void);
void strCopyToBuffer(char* const buffer, char* const str);

/* this copies yytext into yylval for flex */
void moveTokensToYylval();

#endif /* UTIL_H_ */

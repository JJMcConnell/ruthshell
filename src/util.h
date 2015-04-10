#ifndef UTIL_H_
#define UTIL_H_

/*** Utils ***/
void printPrompt(void);
void strCopyToBuffer(char* const buffer, char* const str);

/* should be implemented in any POSIX system */
extern char* strdup(const char* s);

/* this copies yytext into yylval for flex */
void moveTokensToYylval();
void cleanStringBuffer(char* buffer);

#endif /* UTIL_H_ */

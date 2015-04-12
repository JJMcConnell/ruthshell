#ifndef UTIL_H_
#define UTIL_H_

#include "linkedlist.h"

/*** Utils ***/
void printPrompt(void);
void strCopyToBuffer(char* const buffer, char* const str);

/* should be implemented in any POSIX system */
extern char* strdup(const char* s);

/* this copies yytext into yylval for flex */
void moveTokensToYylval();
void cleanStringBuffer(char* buffer);

/* common list walking functions */
int printStringData(Data* d);
int printIntData(Data* d);
int printKeyData(Data* d);

#endif /* UTIL_H_ */

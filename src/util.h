#ifndef UTIL_H_
#define UTIL_H_

#include "arglist.h"
#include "linkedlist.h"

/* inline functions */
#define streq(s1, s2) strcmp(s1, s2) == 0

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

/*
 * If the command has an alias match, this function
 * will re-feed the alias value through the parsing
 * sequence and return true. Otherwise (if there is
 * no alias for the command), returns false.
 */
bool handledCommandWithAlias(char* cmd);

#endif /* UTIL_H_ */

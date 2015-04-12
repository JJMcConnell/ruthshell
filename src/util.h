#ifndef UTIL_H_
#define UTIL_H_

#include <stdbool.h>

#include "arglist.h"

/* inline functions */
#define streq(s1, s2) strcmp(s1, s2) == 0

/*** Utils ***/
void printPrompt(void);

/* should be implemented in any POSIX system */
extern char* strdup(const char* s);

/* this copies yytext into yylval for flex */
void moveTokensToYylval();
void cleanStringBuffer(char* buffer);

/*
 * If the command has an alias match, this function
 * will re-feed the alias value through the parsing
 * sequence and return true. Otherwise (if there is
 * no alias for the command), returns false.
 */
bool handledCommandWithAlias(char* cmd);

#endif /* UTIL_H_ */

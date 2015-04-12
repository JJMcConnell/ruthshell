#ifndef ALIAS_H_
#define ALIAS_H_

#define MAXNUMALIAS 200
#define MAXALIASLENGTH 200

#include <stddef.h>

typedef struct _aliastable {
    char alias[200];
    char cmd[200];
} AliasEntry;

extern AliasEntry aliastab[];
extern size_t aliasCount;

void addAlias(char* alias, char* cmd);
void removeAlias(char* alias);
void moveLeft(size_t i);
void listAllAliases(void);

#endif /* ALIAS_H_ */

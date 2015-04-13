#include "alias.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

AliasEntry aliastab[MAXNUMALIAS];
size_t aliasCount;

void addAlias(char* alias, char* cmd) {
    // check if we should replace any
    size_t i = 0;
    for (i = 0; i < aliasCount; ++i) {
        if (streq(aliastab[i].alias, alias)) {
            //replace
            strcpy(aliastab[i].cmd, cmd);
            return;
        }
    }

    AliasEntry* e = &aliastab[aliasCount++];
    e->cmd[0] = '\0';
    e->alias[0] = '\0';
    strcpy(e->alias, alias);
    strcpy(e->cmd, cmd);
}

void removeAlias(char* alias) {
    size_t i = 0;
    for (i = 0; i < aliasCount; ++i) {
        if (streq(aliastab[i].alias, alias)) {
            // shift all to the right over left
            size_t j = 0;
            for (j = i + 1; j < aliasCount; ++j)
                moveAliasLeft(j);

            --aliasCount;
            return;
        }
    }
}

void moveAliasLeft(size_t i) {
    AliasEntry* e = &aliastab[i];
    AliasEntry* eLeft = &aliastab[i - 1];

    strcpy(eLeft->alias, e->alias);
    strcpy(eLeft->cmd, e->cmd);
}

void listAllAliases(void) {
    size_t i = 0;
    
    for (i = 0; i < aliasCount - 1; ++i)
        printf("%s\n", aliastab[i].alias);
    printf("%s", aliastab[i].alias);
}

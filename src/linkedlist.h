#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <stdbool.h>

/* Enum for choosing data type */
typedef enum {
    DATAINT, DATASTRING, DATAPAIR
} DataType;

/* Support different, but mutually exclusive data types */
typedef struct Data {
    char* s;
    char* key;
    char* value;
    int i;
} Data;

typedef struct LinkedListNode {
    struct Data data; // can be DataInt or DataString
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
    DataType dt;
} LinkedList;

/* These allocate memory! */
LinkedList* createNewLinkedList(DataType dt);
void push(LinkedList* l, Data* d);

/* Deallocates the whole list */
void freeList(LinkedList* l);
/* void pop(LinkedList* l, Data* d); */
void popNode(LinkedList* l, LinkedListNode* n);

/* Walk list, execute func(Data), break if func doesn't return 0 */
void walkAndExecute(LinkedList* l, int (*func)(Data*));

bool dataMatches(Data* d1, Data* d2, DataType t);
/* Searches for first match in list, or returns NULL */
LinkedListNode* findNode(LinkedList* l, Data* d);

#endif /* execute_externel_command */

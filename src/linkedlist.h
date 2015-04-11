#ifndef LINKED_LIST_
#define LINKED_LIST_

/* Enum for choosing data type */
typedef enum {
    DATAINT, DATASTRING
} DataType;

/* Support different, but mutually exclusive data types */
typedef union Data {
    char* s;
    int i;
} Data;

typedef struct LinkedListNode {
    union Data data; // can be DataInt or DataString
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
void pop(LinkedList* l, Data* d);
void popNode(LinkedList* l, LinkedListNode* n);


#endif /* execute_externel_command */

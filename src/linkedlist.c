#include "linkedlist.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"

LinkedList* createNewLinkedList(DataType dt) {
    LinkedList* l = (LinkedList*) malloc(sizeof(LinkedList));
    l->head = NULL;
    l->dt = dt;
    return l;
}

void pop(LinkedList* l, Data* d) {
    LinkedListNode* cur = l->head;

    bool found = false;
    while (cur != NULL && !found) {
        if (l->dt == DATAINT &&
                cur->data.i == d->i) {
            popNode(cur, l->dt);
            break;
        }
        else if (l->dt == DATASTRING &&
                strcmp(cur->data.s, d->s)) {
            popNode(cur, l->dt);
            break;
        }

        // move to the next node
        cur = cur->next;
    }
}

void popNode(LinkedListNode* n, DataType dt) {
    // free a string if that's the dt
    if (dt == DATASTRING)
        free(n->data.s);

    // cut n out of the list
    if (n->prev != NULL)
        n->prev->next = n->next;
    if (n->next != NULL &&
            n->prev != NULL)
        n->next->prev = n->prev;

    // free the node
    free(n);
}

void freeList(LinkedList* l) {
    LinkedListNode* cur = l->head;
    
    while (cur != NULL) {
        LinkedListNode* next = cur->next;
        popNode(cur, l->dt);
        cur = next;
    }

    // free list
    free(l);
}

void push(LinkedList* l, Data* d) {
    LinkedListNode* cur = l->head;

    // base case, empty list
    if (cur == NULL) {
        cur = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        cur->prev = NULL;
        cur->next = NULL;
        l->head = cur;
    }
    else {
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        cur->next->prev = cur;
        cur = cur->next;
    }

    // copy the data, cur is the new node
    if (l->dt == DATAINT)
        cur->data.i = d->i;
    else
        cur->data.s = strdup(d->s);
}

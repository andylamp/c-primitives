/* circular doubly linked list implementation */
#ifndef _LINKED_LIST_D_
    #define _LINKED_LIST_D_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "consts.h"

/* doubly linked list node */
typedef struct _ldcnode {
    void *data;
    struct _ldcnode *next;
    struct _ldcnode *prev;
} ldcnode;

/* add the node in the list */
ldcnode **
listdc_add(ldcnode **head, void *data);

/* remove from the list in specific position */
int
listdc_remove(ldcnode **head, int pos, void * (*cleanup_fnc)(void *));

/* pop the first element from the list */
void *
listdc_pop(ldcnode **head);

/* peak the first element from the list w/o removing it */
void *
listdc_peak(ldcnode **head);

/* destroy the list */
int
listdc_destroy(ldcnode **head, void * (*cleanup_fnc)(void *));

#endif /* _LINKED_LIST_D_ */

/* doubly linked list implementation */
#ifndef _LINKED_LIST_D_
    #define _LINKED_LIST_D_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "consts.h"

/* doubly linked list node */
typedef struct _ldnode {
    void *data;
    struct _ldnode *next;
    struct _ldnode *prev;
} ldnode;

/* add the node in the list */
ldnode **
listd_add(ldnode **head, void *data);

/* remove from the list in specific position */
int
listd_remove(ldnode **head, int pos, void * (*cleanup_fnc)(void *));

/* pop the first element from the list */
void *
listd_pop(ldnode **head);

/* peak the first element from the list w/o removing it */
void *
listd_peak(ldnode **head);

/* destroy the list */
int
listd_destroy(ldnode **head, void * (*cleanup_fnc)(void *));

#endif /* _LINKED_LIST_D_ */

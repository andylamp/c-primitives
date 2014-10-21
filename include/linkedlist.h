/* simple linked list */

#ifndef _LINKED_LIST_H
   #define _LINKED_LIST_H

#include <stdlib.h>
#include <unistd.h>
#include "consts.h"

typedef struct _lnode {
   void *data;
   struct _lnode *next;   
} lnode;

/* our function pointer for cleanup function */
//void * (*cleanup_fnc_ptr)(void *);

/* push to the list */
lnode **
list_add(lnode **head, void *data);

/* remove an element */
int
list_remove(lnode **head, int pos, void * (*cleanup_fnc)(void *));

/* pop the first element */
void *
list_pop(lnode **head);

/* peak the first element w/o removing it */
void *
list_peak(lnode **head);

/* free up the resources */
int
list_destroy(lnode **head, void * (*cleanup_fnc)(void *));

#endif /* _LINKED_LIST_H */


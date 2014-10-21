/* simple linked list */

#include "linkedlist.h"

/* push to the list */
lnode **
list_add(lnode **head, void *data) {
   lnode *node = NULL;
   /* check if we allocated the req. memory */
   if((node = calloc(1, sizeof(lnode))) == NULL)
      {return(NULL);}
   /* add the data */
   node->data = data;
   /* update the next pointer of new node */ 
   node->next = *head;
   /* update head pointer */
   *head = node;
   /* and return it */
   return(head);
}

/* remove an element */
int
list_remove(lnode **head, int pos, void * (*cleanup_fnc)(void *)) {
   lnode **trav = head,
         *tmp = NULL;
   int i = 0;
   /* traverse the required positions */
   while(*trav != NULL && i < pos-1) 
      {trav = &((*trav)->next); i++;}
   /* if we didn't have that many elements */
   if((*trav)->next == NULL) {return(FAIL);}
   /* actually erase the element */
   tmp = *trav;
   *trav = (*trav)->next;
   /* check if we have a clean-up function for data */
   if(cleanup_fnc) 
      {(tmp)->data = (*cleanup_fnc)(tmp);}
   else 
      {free((tmp)->data);}
   free(tmp);
   /* return, proud with success */
   return(TRUE);
}

/* pop the first element */
void *
list_pop(lnode **head) {
   lnode *n = *head;
   *head = (*head)->next;
   return(n);
}

/* peak the first element w/o removing it */
void *
list_peak(lnode **head) 
   {return(*head);}

/* free up the resources */
int
list_destroy(lnode **head, void * (*cleanup_fnc)(void *)) {
   lnode *trav = *head;
   /* null input */
   if(*head == NULL) {return(FAIL);}

   /* now traverse, and free */
   while(*head != NULL) {
      trav = (*head)->next;
      /* check if we have a clean-up function for data */
      if(cleanup_fnc) 
         {(*head)->data = (*cleanup_fnc)(*head);}
      else 
         {free((*head)->data);}
      free(*head);
      *head = trav;
   }
   /* return null either-way */
   return(TRUE);
}

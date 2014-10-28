/* doubly linked list implementation */

#include "linkedlistd.h"

/* add the node in the list */
ldnode **
listd_add(ldnode **head, void *data) {
    ldnode *tnode = NULL;
    /* parameter check */
    if(data == NULL)
        {return(NULL);}
    /* allocate the node */
    if((tnode = (calloc(1, sizeof(*tnode)))) == NULL)
        {return(NULL);}
    /* update the prev */
    tnode->prev = NULL;
    /* update the data */
    tnode->data = data;
    /* update the next */
    tnode->next = *head;
    /* head already exists, update the prev */
    if(*head != NULL) 
        {(*head)->prev = tnode;}
    /* finally update the head of the list */
    *head = tnode;
    /* return it */
    return(head);
}

/* remove from the list in specific position */
int
listd_remove(ldnode **head, int pos, void * (*cleanup_fnc)(void *)) {
    ldnode **tnode = head,
            *tmp = NULL;
    int i = 0;
    /* check if we have valid input */
    if(head == NULL || *head == NULL || pos < 0)
      {return(FAIL);} 
    /* now traverse */
    while(*tnode != NULL && i < pos-1) 
      {tnode = &((*tnode)->next); i++;}
    /* chek if we reached the position */
    if(i != (pos-1) || *tnode == NULL) 
      {return(FAIL);}

    tmp = *tnode;
    *tnode = (*tnode)->next;
    (*tnode)->prev = tmp->prev;
    /* clean up data */ 
    if(cleanup_fnc != NULL) 
      {tmp->data = (*cleanup_fnc)(tmp);}
    else
      {if(tmp->data) {free(tmp->data);}}
    /* free up node, finally */
    free(tmp);

    return(TRUE);
}

/* pop from the list */
void *
listd_pop(ldnode **head) {
   ldnode *tnode = NULL;
   void *ptr = NULL;
   /* check if we can pop */
   if(head == NULL || *head == NULL)
      {return(NULL);}
   
   tnode = *head;
   ptr = tnode->data;

   /* update head pointers */
   *head = (*head)->next;
   (*head)->prev = NULL;
   /* free the node */
   free(tnode);
   /* now return the data */
   return(ptr);
}

/* peak the first element from the list w/o removing it */
void *
listd_peak(ldnode **head) 
   {return((head != NULL && *head != NULL) ? (*head)->data : NULL);}

/* destroy the list */
int
listd_destroy(ldnode **head, void * (*cleanup_fnc)(void *)) {
    ldnode *tnode = NULL;
    /* check if we have an valid head */
    if(head == NULL)
        {return(FAIL);}
    /* loop until we reach the end */
    while(*head != NULL) {
        tnode = *head;
        *head = (*head)->next;
        if(cleanup_fnc != NULL) 
            /* use clean up function */
            {tnode->data = (*cleanup_fnc)(tnode);} 
        /* no clean-up function present */
        else 
            {if(tnode->data) {free(tnode->data);}}
        free(tnode);
    }
    return(TRUE);
}


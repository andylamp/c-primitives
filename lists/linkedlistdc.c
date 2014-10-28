/* circular doubly linked list implementation */

#include "linkedlistdc.h"

/* add the node in the list */
ldcnode **
listdc_add(ldcnode **head, void *data) {
    ldcnode *tnode = NULL;
    /* parameter check */
    if(data == NULL)
        {return(NULL);}
    /* allocate the node */
    if((tnode = (calloc(1, sizeof(*tnode)))) == NULL)
        {return(NULL);}
    /* update the prev */
    //tnode->prev = ;
    /* update the data */
    tnode->data = data;
    /* update the next */
    //tnode->next = *head;
    /* head already exists, update the prev */
    if(*head != NULL) {
       tnode->prev = (*head)->prev;
       tnode->next = (*head); 
       (*head)->prev = tnode;
    }
    else
      {tnode->prev = tnode; tnode->next = tnode;}
    /* finally update the head of the list */
    *head = tnode;
    /* return it */
    return(head);
}

/* remove from the list in specific position */
int
listdc_remove(ldcnode **head, int pos, void * (*cleanup_fnc)(void *)) {
    ldcnode **tnode = head,
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
listdc_pop(ldcnode **head) {
   ldcnode *tnode = NULL;
   void *ptr = NULL;
   /* check if we can pop */
   if(head == NULL || *head == NULL)
      {return(NULL);}
   
   tnode = *head;
   ptr = tnode->data;

   /* update head pointers */
   *head = (*head)->next;
   (*head)->prev = tnode->prev;
   /* free the node */
   free(tnode);
   /* now return the data */
   return(ptr);
}

/* peak the first element from the list w/o removing it */
void *
listdc_peak(ldcnode **head) 
   {return((head != NULL && *head != NULL) ? (*head)->data : NULL);}

/* destroy the list */
int
listdc_destroy(ldcnode **head, void * (*cleanup_fnc)(void *)) {
    ldcnode *tnode = NULL,
            *break_addr = NULL;
    /* check if we have an valid head */
    if(head == NULL)
        {return(FAIL);}
    break_addr = (*head)->prev;
    /* loop until we reach the end */
    while(break_addr != NULL) {
        tnode = *head;
        *head = (*head)->next;
        if(break_addr == *head) {break_addr = NULL;}
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


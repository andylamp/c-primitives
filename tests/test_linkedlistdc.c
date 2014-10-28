/* test doubly linked list */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "linkedlistdc.h"

void *
demo_cleanup_fnc(void *arg) {
   ldcnode *dat = (ldcnode *)arg;
   // do the free's we want
   if(dat->data) {free(dat->data);}
   return(NULL);
}

void * (*cleanup_fnc_ptr)(void *);


/* main stub */
int
main(int argc, char **argv) {

   ldcnode *lptr = NULL,
         *trav = NULL,
        **head = &lptr;
   int i,
       iter = 10, 
       *item = NULL;

   /* w/o clean-up function */
   printf("\n\nTesting without cleanup function...\n");
   for(i = 0; i < 10; i++) {
      item = (int *)calloc(1, sizeof(int));
      *item = i;
      head = listdc_add(head, (void *)item);
   }
   trav = lptr;
   for(i = 0; i < 10; i++) {
     printf("\n !! Element no %d with val: %d (prev val: %d)", 
           i, *((int *)trav->data), *(int *)(trav->prev->data));
     trav = trav->next; 
   }

   listdc_remove(head, 4, NULL);

   listdc_destroy(head, NULL);

   /* with clean up function */
   printf("\n\nTesting with cleanup function...\n");
   cleanup_fnc_ptr = &demo_cleanup_fnc;

   for(i = 0; i < iter; i++) {
      item = (int *)calloc(1, sizeof(int));
      *item = i;
      head = listdc_add(head, (void *)item);
   }

   trav = lptr;
   for(i = 0; i < iter; i++) {
     printf("\n !! Element no %d with val: %d", i, *((int *)trav->data));
     trav = trav->next; 
   }
   
   printf("\n");
   listdc_remove(head, 4, cleanup_fnc_ptr);
   listdc_remove(head, 2, cleanup_fnc_ptr);
   trav = lptr;
   for(i = 0; i < iter-2; i++) {
     printf("\n !! Element no %d with val: %d (prev val: %d)", 
           i, *((int *)trav->data), *(int *)(trav->prev->data));
     trav = trav->next; 
   }   
   printf("\n\n");
   listdc_destroy(head, cleanup_fnc_ptr);

   return(EXIT_SUCCESS);
}


/* stub to test the linked list */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "linkedlist.h"

void *
demo_cleanup_fnc(void *arg) {
   lnode *dat = (lnode *)arg;
   // do the free's we want
   if(dat->data) {free(dat->data);}
   return(NULL);
}

void * (*cleanup_fnc_ptr)(void *);

/* our main stub */
int
main(int argc, char **argv) {

   lnode *lptr = NULL,
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
      head = list_add(head, (void *)item);
   }
   trav = lptr;
   for(i = 0; i < 10; i++) {
     printf("\n !! Element no %d with val: %d", i, *((int *)trav->data));
     trav = trav->next; 
   }

   list_remove(head, 4, NULL);

   list_destroy(head, NULL);

   /* with clean up function */
   printf("\n\nTesting with cleanup function...\n");
   cleanup_fnc_ptr = &demo_cleanup_fnc;

   for(i = 0; i < iter; i++) {
      item = (int *)calloc(1, sizeof(int));
      *item = i;
      head = list_add(head, (void *)item);
   }

   trav = lptr;
   for(i = 0; i < iter; i++) {
     printf("\n !! Element no %d with val: %d", i, *((int *)trav->data));
     trav = trav->next; 
   }
   
   printf("\n");
   list_remove(head, 4, cleanup_fnc_ptr);

   trav = lptr;
   for(i = 0; i < iter-1; i++) {
     printf("\n !! Element no %d with val: %d", i, *((int *)trav->data));
     trav = trav->next; 
   }   
   printf("\n\n");
   list_destroy(head, cleanup_fnc_ptr);

   return(EXIT_SUCCESS);
}

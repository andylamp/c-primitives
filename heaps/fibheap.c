/* implementation of a (min) fibonnaci heap */

#include "fibheap.h"

/* insert to the heap */
fibheap **
fibheap_insert(fibheap **fhead, void *data) {

   fibnode *fnode = NULL;
   /* check for valid parameters */
   if(fhead == NULL || data == NULL)
      {return(NULL);}
   /* allocate node */
   if((fnode = calloc(1, sizeof(*fnode))) == NULL)
      {return(NULL);}
   /* initialize the node */
   fnode->degree = 0;
   fnode->p = NULL;
   fnode->child = NULL;
   fnode->marked = FALSE;

   /* create a root list */
   if(*fhead == NULL) {
      ;
   } 
   /* insert node into the root list */
   else {
      ;
   }
   return(NULL);
}


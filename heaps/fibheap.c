/* implementation of a (min) fibonnaci heap */

#include "fibheap.h"

/* insert to the heap */
fibheap **
fibheap_insert(fibheap **fhead, void *data) {
   /* node pointer */
   fibnode *fnode = NULL;
   fibheap *fheap = NULL;
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
      /* allocate the node */
      if((fheap = calloc(1, sizeof(*fheap))) == NULL)
         {return(NULL);}
      /* set number of nodes to 1 */
      fheap->nodes = 0;
      /* now create the first ordered heap */
      fheap->min_node = NULL;
   } 
   /* insert node into the root list */
   else {
      ;
   }
   return(NULL);
}


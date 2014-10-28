/* implementation of a (min) fibonnaci heap */
#ifndef _FIB_HEAP_H_
   #define _FIB_HEAP_H_
/* our defines */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "consts.h"
#include "linkedlistd.h"

/* fibonacci heap node */
typedef struct _fibnode {
   int degree;
   int marked;
   //struct _fibnode *p;
   //struct _fibnode *child;
   ldnode *p;
   ldnode *child;
} fibnode;

/* fibonacci heap structure */
typedef struct _fibheap {
   int nodes;
   ldnode *min_node;
} fibheap;

/* insert to the heap */
fibheap **
fibheap_insert(fibheap **fhead, void *data);



#endif /* _FIB_HEAP_H_ */


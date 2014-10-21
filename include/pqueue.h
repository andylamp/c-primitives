
#ifndef P_QUEUE_
   #define P_QUEUE_
#include <stdio.h>
#include <stdlib.h>
#include "consts.h"

#ifndef PQ_MIN_SZ
   #define PQ_MIN_SZ 8
#endif

/* priority queue element */
typedef struct {
   void *item;
   int  item_p;
} pq_item;

/* priority queue data structure */
typedef struct {
   pq_item *pq_link;
   int n, allocs;
} pq_t, *pq_ptr;

/* create a priority queue */
pq_ptr 
pq_create(int maxsize);

/* returns the priority queue occupacy */
int
pq_size(pq_ptr pq, int *alloced);

/* push into a priority queue */
int
pq_push(pq_ptr pq, void *itemdat, int item_p, int unique);

/* decrease a key priority */
int
pq_decrease_priority(pq_ptr pq, void *itemdat, int new_item_p); 

/* pop from a priority queue */
void *
pq_pop(pq_ptr pq, int *prefp);

/* retrieve top item, w/o removal */
void *
pq_peak(pq_ptr pq, int *prefp);

/* destroy priority queue */
int
pq_destroy(pq_ptr pq);

#endif

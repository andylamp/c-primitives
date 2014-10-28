 
 #include "pqueue.h"
 
 /* create a priority queue */
 pq_ptr 
 pq_create(int maxsize) {
   int pq_size = maxsize;
   pq_ptr pq = NULL;

   if(pq_size < PQ_MIN_SZ) {pq_size = PQ_MIN_SZ;}

   /* check if we are OK */
   if((pq = calloc(1, sizeof(pq_t))) == NULL)
      {return(NULL);}

   if((pq->pq_link = calloc(pq_size, sizeof(pq_item))) == NULL)
      {if(pq != NULL) {free(pq);} return(NULL);}

   /* set size and current elements */
   pq->allocs = pq_size;
   pq->n = 1;

   /* finally return it */
   return(pq);
}

/* destroy priority queue */
int
pq_destroy(pq_ptr pq) {
    if(pq != NULL) {
       if(pq->pq_link != NULL) 
           {free(pq->pq_link);} 
       free(pq); 
       return(TRUE);
    }
    return(FAIL);
}

/* returns the priority queue occupacy */
int
pq_size(pq_ptr pq, int *alloced)
    {if(alloced != NULL) {*alloced = pq->allocs;} return(pq->n-1);}

/* push into a priority queue */
int
pq_push(pq_ptr pq, void *itemdat, int item_p, int unique) {
   int pos, trav;

   if(pq == NULL || itemdat == NULL) {return(-1);}

   /* grow the space, if needed */
   if(pq->n >= pq->allocs) {
      pq->allocs = pq->allocs * 2;
      if((pq->pq_link = realloc(pq->pq_link, 
                  pq->allocs * sizeof(pq_item))) == NULL)
         {if(pq) {free(pq);} return(FAIL);}
   }

   pos = pq->n++;

   /* pad at the end, then push up to the heap */
   while((trav = (pos/2)) && item_p < pq->pq_link[trav].item_p) 
      {pq->pq_link[pos] = pq->pq_link[trav]; pos = trav;} 

   /* place the values */
   pq->pq_link[pos].item = itemdat;
   pq->pq_link[pos].item_p = item_p;
   return(TRUE);
}

/* sneaky swap */
void
swap_with_parent(pq_ptr pq, int *i) {
   pq->pq_link[0].item_p = pq->pq_link[(*i)/2].item_p;
   pq->pq_link[0].item = pq->pq_link[(*i)/2].item;

   pq->pq_link[(*i)/2].item = pq->pq_link[*i].item;
   pq->pq_link[(*i)/2].item_p = pq->pq_link[*i].item_p;

   pq->pq_link[*i].item = pq->pq_link[0].item;
   pq->pq_link[*i].item_p = pq->pq_link[0].item_p;
}

/* decrease a key priority */
int
pq_decrease_priority(pq_ptr pq, void *itemdat, int new_item_p) {
   int i = 1;
   if(pq == NULL || itemdat == NULL || 
      new_item_p < 0)
      {return(FAIL);} 

   /* this is actually cheating... but I like it. */
   for(i = 1; i < pq->n; i++) 
      {if(itemdat == pq->pq_link[i].item) {break;}}
   
   /* not in queue */
   if(i == pq->n) 
      {dbg(printf("Alloc is: %d, i is: %d", pq->allocs, i);); return(FAIL);}
  
   /* now adjust it */
   if(pq->pq_link[i].item_p < new_item_p)
      {return(FAIL);}
   /* update priority */
   pq->pq_link[i].item_p = new_item_p; 
   
   /* maintain heap invariant */
   while(i > 1  && (pq->pq_link[i/2].item_p > new_item_p)) {
      /* swap */
      swap_with_parent(pq, &i);
      /* parent */
      i = i/2;
   }
    
   return(TRUE);
}

/* pop from a priority queue */
void *
pq_pop(pq_ptr pq, int *prefp) {
   void *pop_item = NULL;
   int pos = 1, trav;
   /* our queue is empty */
   if(pq->n == 1) {return(NULL);}
   /* give a pointer to the item */
   pop_item = pq->pq_link[1].item;
   /* return the priority of the pop'ed item */
   if(prefp != NULL) {*prefp = pq->pq_link[1].item_p;}

   /* reduce elements in queue */   
   pq->n--;

   while((trav = pos*2) < pq->n) {
      if( (trav+1) < pq->n && pq->pq_link[trav].item_p > pq->pq_link[trav+1].item_p) {trav++;}
      if(pq->pq_link[pq->n].item_p <= pq->pq_link[trav].item_p) {break;}
      pq->pq_link[pos] = pq->pq_link[trav];
      pos = trav;
   }

   pq->pq_link[pos] = pq->pq_link[pq->n];

   /* check if we neeed to downsize */
   if(pq->n < pq->allocs/2 && pq->n > 2*PQ_MIN_SZ) {
      if((pq->pq_link = realloc(pq->pq_link, (pq->allocs /= 2) * sizeof(pq_item))) == NULL)
         {if(pq != NULL) {free(pq);} return(NULL);}
   }
   /* finally return the pop'ed item */
   return(pop_item);
}

/* retrieve top item, w/o removal */
void *
pq_peak(pq_ptr pq, int *prefp) {
   if(pq->n == 1) {return(NULL);}
   if(pq != NULL && pq->pq_link != NULL) 
      {*prefp = pq->pq_link[1].item_p; return(pq->pq_link[1].item);}
   /* else return null */
   return(NULL);
}

/* our defines */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pqueue.h"

/* our main stub */
int 
main(int argc, char **argv) {

  int i = 0, 
      p_tmp = 0;
  const char   *res = NULL, 
               *strdat[] = {
                     "T1", 
                     "T2", 
                     "T3", 
                     "T5", 
                     "T6",
                     "T3" };
  int strprio[] = { 2, 10, 3, 9, 9, 2 };
 

   pq_ptr pq = NULL;

   pq = pq_create(2*PQ_MIN_SZ);

  /* push all 5 tasks into q */
  for (i = 0; i < 6; i++)
    pq_push(pq, (char *)strdat[i], strprio[i], FALSE);
    
  pq_decrease_priority(pq, (char *)strdat[2], 0);
  /* pop them and print them */ 
  for(i = 0; i < 6; i++) {
     res = pq_pop(pq, &p_tmp);   
     printf("Element: %s with priority: %d\n", res, p_tmp);
   }
   /* clear the queue */
   pq_destroy(pq);

   return(EXIT_SUCCESS);
}

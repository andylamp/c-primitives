
#include "graph_search.h"

/* djikstra single source shortest paths algorithm */
int
djikstra_ss_sp(pgraph *graph, gsvertex *src_vertex) {

   int i = 0,
       vindex = UNDEFINED,
       vprio = UNDEFINED;
   /* our priority queue */
   pq_ptr pq = NULL;
   /* our temp vertex pointers */
   gsvertex *t_vertex = NULL;

   /* check if we have "valid" parameters */
   if(graph == NULL || src_vertex == NULL) 
      {return(FAIL);}

   /* initialize our priotiry queue */
   pq = pq_create(PQ_MIN_SZ*2); // def. is 16

   /* initialize the graph for searching  */
   dbg(printf("\nInitializing graph and searching for source vertex...\n"););
   for(i = 0; i < graph->vert_num; i++) {
      if(graph->vertices[i] == src_vertex) {
         dbg(printf("\n\t !! Found source vertex (it's %s, idx: %d) "
            "in graph, marking it.", graph->vertices[i]->vname, i););
         graph->vdist[i] = 0;
         vindex = i;
      } else 
         /* set all other distances to max val */
         {graph->vdist[i] = INT_MAX/2;}
      /* push it in the p. queue */
      pq_push(pq, graph->vertices[i], graph->vdist[i], TRUE);
      /* set graph predecessor to undefined */
      graph->vprev[i] = UNDEFINED;
   }
   /* we need a source vertex, if not found... return */
   if(vindex == UNDEFINED) {
      dbg(printf("\nSource vertex not found... can't search\n"););
      return(FAIL);
   }

   dbg(printf("\n\nSearching in graph using Dijkstra's" 
        "algorithm...(queue size is: %d)\n", pq->n-1););
   
   /* while queue has elements */
   while(pq_size(pq, NULL) > 0) {
     /* pop from queue */
     t_vertex = (gsvertex *)pq_pop(pq, &vprio);
     dbg(printf("\n\t !! pop'ed from queue vertex %s with priority %d,"
        " queue size is: %d", t_vertex->vname, vprio, pq->n-1););
     /* mark it as visited */
     dbg(printf("\n\t   -- Marking vertex %s as visited (has %d neighbors)", 
           t_vertex->vname, t_vertex->vneighbor_num););

     t_vertex->visited = TRUE;
     /* loop through neighbors of vertex */
     for(i = 0; i < t_vertex->vneighbor_num; i++) {
        /* if we have not visited the vertex yet */
        if(t_vertex->vneighbors[i].vpointer->visited == FALSE) {
            dbg(printf("\n\t   ** Neighbor %s of %s is NOT visited yet, probing",
                  t_vertex->vneighbors[i].vpointer->vname, t_vertex->vname););
            /* update priority (distance) */
            vprio = graph->vdist[t_vertex->index] + t_vertex->vneighbors[i].dist;
            dbg(printf("\n\t\t -- Priority is: %d vdist is: %d\n", 
                  vprio, graph->vdist[t_vertex->vneighbors[i].vpointer->index]););       
            /* now check if we need to add */
            if(vprio < graph->vdist[t_vertex->vneighbors[i].vpointer->index]) {
               graph->vdist[t_vertex->vneighbors[i].vpointer->index] = vprio;
               graph->vprev[t_vertex->vneighbors[i].vpointer->index] = t_vertex->index;
               /* push to queue if not inside already (using unique flag) */
               pq_decrease_priority(pq, 
                     graph->vertices[t_vertex->vneighbors[i].vpointer->index], vprio);
               dbg(printf("\n\t\t  -- Decreasing priority of %s with %d from %s\n", 
                     graph->vertices[t_vertex->vneighbors[i].vpointer->index]->vname, 
                     vprio, t_vertex->vname););
            }

        } 
     }
   }
   /* after the loop we should have the correct path 
    * in prev array of our graph! */

   /* clean up our queue */
   pq_destroy(pq);
   return(TRUE);
}


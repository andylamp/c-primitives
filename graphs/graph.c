
#include "graph.h"

/* clear our graph */
int
clear_graph(pgraph *gstruct, void * (*cleanup_fnc)(void *)) {
   int i = 0;
   if(gstruct == NULL) {return(FAIL);}
   /* clean up the easy stuff */
   if(gstruct->vdist) {free(gstruct->vdist);}
   if(gstruct->vprev) {free(gstruct->vprev);}
   /* now the tricky part */
   if(cleanup_fnc != NULL) 
      {/* use clean up fnc */}
   else {
      printf("\n\nCleaning without a function (default)\n\n");
      /* clean-up neighbor buffers */
      if(gstruct->vertices) { 
         for(i = 0; i < gstruct->vert_num; i++) {
            if(gstruct->vertices[i]) {
               if(gstruct->vertices[i]->vneighbors)
                  {free(gstruct->vertices[i]->vneighbors);}
               free(gstruct->vertices[i]);   
            }
         }
         /* finally clear up the vertice pointers */
         free(gstruct->vertices);
      } 
   }
   /* finally free the structure itself */
   free(gstruct);
   return(TRUE);
}

/* allocate resources for our graph */
pgraph *
initialze_graph(int initsize) {
   int size = initsize;
   pgraph *gstruct = NULL;
   if(size <= 0)
      {size = INITIAL_GRAPH_BUF_SIZE;}
  /* long allocation if! */ 
  if( ((gstruct = calloc(1, sizeof(pgraph))) == NULL) ||
       ((gstruct->vdist = calloc(size, sizeof(int))) == NULL) ||
       ((gstruct->vprev = calloc(size, sizeof(int))) == NULL) ||
       ((gstruct->vertices = calloc(size, sizeof(gsvertex))) == NULL) )
      {clear_graph(gstruct, NULL); return(NULL);}

   /* initialize the vertex number to zero */
   gstruct->vert_num = 0; 
   gstruct->allocated = size;
   /* finally return the initialized graph */
   return(gstruct);
}

/* add a vertex to the graph */
int
add_vertex(pgraph *gstruct, gsvertex *vertex) {
   if(gstruct == NULL || vertex == NULL )// || *vertex == NULL)
      {return(FAIL);}
   /* increase the vertex count */
   gstruct->vert_num++;
   /* check if we need to reallocate */
   if(gstruct->vert_num > gstruct->allocated) {
      /* increase them */
      if(((gstruct->vdist = realloc(gstruct->vdist, 
                     gstruct->allocated*2*sizeof(int))) == NULL) ||
         ((gstruct->vprev = realloc(gstruct->vprev, 
                     gstruct->allocated*2*sizeof(int))) == NULL) ||
         ((gstruct->vertices = realloc(gstruct->vertices, 
                     gstruct->allocated*2*sizeof(gsvertex))) == NULL) )
         {clear_graph(gstruct, NULL); return(FAIL);}
      /* update allocated count */
      gstruct->allocated *= 2;
   }
   /* set the index */
   vertex->index = gstruct->vert_num-1;
   /* update vertex parameters */
   gstruct->vdist[gstruct->vert_num-1] = 0;
   gstruct->vprev[gstruct->vert_num-1] = -1;
   gstruct->vertices[gstruct->vert_num-1] = vertex;
   return(TRUE);
}

/* function to instantiate a vertex */
gsvertex *
create_vertex(char *name) {
   /* our tmp instance */
   gsvertex *vertex = NULL;
   /* type check */
   if(name == NULL || (strlen(name)-1) > MAX_VERTEX_NAME_LEN) 
      {return(NULL);}
   /* try to allocate the required memory */
   if((vertex = calloc(1, sizeof(*vertex))) == NULL)
      {return(NULL);} 
   /* set the visited status to false */
   vertex->visited = FALSE;
   /* copy the name */
   strncpy(vertex->vname, name, sizeof(vertex->vname)-1);
   /* pad null, just in case */
   vertex->vname[MAX_VERTEX_NAME_LEN-1] = '\0';

   /* allocate the neighbors */    
   if((vertex->vneighbors = calloc(INITIAL_NEIGHBOR_BUF_SIZE, 
               sizeof(struct _vneighbor))) == NULL)
      {if(vertex) {free(vertex);} return(NULL);}
   vertex->vneighbor_num = 0;
   vertex->allocated = INITIAL_NEIGHBOR_BUF_SIZE;
  
   /* return the vertex */
   return(vertex);
}

/* add a neighbor to a vertex */
int
add_vertex_neighbor(gsvertex *vertex, gsvertex **vneighbor, int dist) {
   /* type check */
   if(vertex == NULL || vneighbor == NULL || dist <= 0)
      {return(FAIL);}

   vertex->vneighbor_num++;
   /* check if we need to grow */
   if(vertex->vneighbor_num >= vertex->allocated) {
      if((vertex->vneighbors = realloc(vertex->vneighbors, 
          vertex->allocated*2*sizeof(struct _vneighbor))) == NULL)
         /* careful, not free'ed! should do it later! */
         {return(FAIL);}
      /* update allocated count */
      vertex->allocated *= 2;
   }
   /* update parameters */
   vertex->vneighbors[vertex->vneighbor_num-1].dist = dist;
   vertex->vneighbors[vertex->vneighbor_num-1].vpointer = *vneighbor;
   return(TRUE);
}

/* parse the adjacency list */
int
parse_adjacency_list(gsvertex **vlist, int adj_list[][2], int vnum) {
   int vindex = 0,
       adj_index = 0;
   /* parse for all vertices */
   for(vindex = 0; vindex < vnum; vindex++) {
      while(1) {
         //printf("\n vindex: %d adjlist %d %d idx: %d", 
         //vindex, adj_list[adj_index][0], 
         //adj_list[adj_index][1], adj_index);
         /* check if we need to end */
         if(adj_list[adj_index][0] == -1 && 
            adj_list[adj_index][1] == -1)
            {vindex = vnum; break;}  
         /* check if we have a spacer */
         else if(adj_list[adj_index][0] == 0 &&
                 adj_list[adj_index][1] == 0) 
            /* if we do, advance */
            {adj_index++; break;}
         /* check actual values */
         else if(adj_list[adj_index][0] < -1 ||
                 adj_list[adj_index][0] == vindex ||
                 adj_list[adj_index][0] >= vnum ||
                 adj_list[adj_index][1] < -1)
            {return(FAIL);}
         /* add to the target vertex, the neighbor and it's distance */ 
         else
            {add_vertex_neighbor(vlist[vindex], &vlist[adj_list[adj_index][0]], adj_list[adj_index][1]); adj_index++;}
      }
   }
   return(TRUE);
}

/* print single-source shortest paths */
int
print_single_source_sp(pgraph *gstruct, gsvertex *source) {
   int i = 0, j = 0;
   char *sv_name = source->vname;
   /* check input */
   if(gstruct == NULL || source == NULL)
      {return(FAIL);}

   printf("\n\nPrinting all single-source shortest paths from %s\n", sv_name);
   for(i = 0; i < gstruct->vert_num; i++) {
      printf("\n -- Printing shortest path from %s -> %s\n\t ** Path: %s ", 
            sv_name, gstruct->vertices[i]->vname, gstruct->vertices[i]->vname);
      j = i;
      while(j >= 0 && j < gstruct->vert_num &&
            gstruct->vdist[j] != 0) {
         printf("-> %s ", gstruct->vertices[gstruct->vprev[j]]->vname);
         j = gstruct->vprev[j]; 
      }
   }
   return(TRUE);
}

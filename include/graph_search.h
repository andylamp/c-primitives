#ifndef _GRAPH_SEARCH_
    #define _GRAPH_SEARCH_

/* our includes */
#include "consts.h"
#include "pqueue.h"
#include "graph.h" 

/* djikstra single source shortest paths algorithm */
int
djikstra_ss_sp(pgraph *graph, gsvertex *src_vertex);   
    
#endif

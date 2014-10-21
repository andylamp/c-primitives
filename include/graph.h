#ifndef _GRAPH_LIB_H_
    #define _GRAPH_LIB_H_
    
/* our defines */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "consts.h"

/* clear our graph */
int
clear_graph(pgraph *gstruct, void * (*cleanup_fnc)(void *));

/* allocate resources for our graph */
pgraph *
initialze_graph(int initsize);

/* add a vertex to the graph */
int
add_vertex(pgraph *gstruct, gsvertex *vertex);

/* function to instantiate a vertex */
gsvertex *
create_vertex(char *name);

/* add a neighbor to a vertex */
int
add_vertex_neighbor(gsvertex *vertex, gsvertex **vneighbor, int dist);

/* parse the adjacency list */
int
parse_adjacency_list(gsvertex **vlist, int adj_list[][2], int vnum);

/* print single-source shortest paths */
int
print_single_source_sp(pgraph *gstruct, gsvertex *source);

#endif /* _GRAPH_LIB_H_ */

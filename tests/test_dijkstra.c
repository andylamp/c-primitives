/* our defines */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "consts.h"
#include "pqueue.h"
#include "graph.h"
#include "graph_search.h"
//#include "linkedlist.h"

/* our main stub */
int 
main(int argc, char **argv) {

   int i = 0,
       num_verts = 8;
   pgraph *gstruct = NULL;

   char char_buf[10];

   bzero(char_buf, sizeof(char_buf)); 

   gsvertex **graph_vertex_array = NULL;

   gstruct = initialze_graph(0);

   graph_vertex_array = calloc(num_verts, sizeof(*graph_vertex_array));
  
   /* create some vertices */

   /* it's 8 vertices with names ranging from A -> H */
   printf("\nCreating vertices to add in graph\n");
   for(i = 0; i < num_verts; i++) {
      char_buf[0] = (char)(i+65);
      printf("\n\t !! Creating vertex: %s", char_buf); 
      graph_vertex_array[i] = create_vertex(char_buf);
   }
   printf("\n\nFinished creating vertices");


   /*
    * The adjacency list is as follows:
    *
    * Vertex A (i:0): [ B (i:1), 7 ] , [ C (i:2), 8 ]
    * Vertex B (i:1): [ A (i:0), 7 ] , [ F (i:5), 2 ]
    * Vertex C (i:2): [ A (i:0), 8 ] , [ F (i:5), 6 ] , [ G (i:6), 4 ]
    * Vertex D (i:3): [ F (i:5), 8 ]
    * Vertex E (i:4): [ H (i:7), 1 ]
    * Vertex F (i:5): [ B (i:1), 2 ] , [ C (i:2), 6 ] , [ D (i:3), 8 ] , [ G (i:6), 9 ] , [ H (i:7), 3 ]
    * Vertex G (i:6): [ C (i:2), 4 ] , [ F (i:5), 9 ]
    * Vertex H (i:7): [ F (i:5), 3 ] , [ E (i:4), 1 ]
    *
    */

   /* 
    * Format is: 
    *
    *   {v0,d},
    *      .
    *      .
    *      .
    *    {0,0}, // Spacer
    *   {v1,d}
    *      .
    *      .
    *      .
    *   {-1,-1} // end
    *    
    *
    */
   int adj_list[][2] =  {
      // Vertex A (i:0)
      {1,7},
      {2,8},
      // spacer
      {0,0},
      // Vertex B (i:1)
      {0,7},
      {5,2},
      // spacer
      {0,0},
      // Vertex C (i:2)
      {0,8},
      {5,6},
      {6,4},
      // Spacer
      {0,0},
      // Vertex D (i:3)
      {5,8},
      // Spacer
      {0,0},
      // Vertex E (i:4)
      {7,1},
      // Spacer
      {0,0},
      // Vertex F (i:5)
      {1,2},
      {2,6},
      {3,8},
      {6,9},
      {7,3},
      // Spacer
      {0,0},
      // Vertex G (i:6)
      {2,4},
      {5,9},
      // Spacer
      {0,0},
      // Vertex H (i:7)
      {5,3},
      {4,1},
      // Ending
      {-1,-1}
   };

   /* add the adjacency list */
   printf("\n\nAdding vertex neighbors\n");
   parse_adjacency_list(graph_vertex_array, adj_list, num_verts);
   printf("Finishing adding vertex neighbors");
 
   /* add the completed vertices to the graph */
   printf("\n\nPlacing created vertices in the graph\n");
   for(i = 0; i < num_verts; i++) {
      printf("\n\t !! Adding to graph vertex %s", graph_vertex_array[i]->vname);
      add_vertex(gstruct, graph_vertex_array[i]); 
   }
   printf("\n\nFinished loading the vertices in the graph\n");

   /* seach the graph */
   djikstra_ss_sp(gstruct, gstruct->vertices[1]);

   /* print the all paths from source */
   print_single_source_sp(gstruct, gstruct->vertices[1]);

   /* destroy our graph */
   clear_graph(gstruct, NULL);

   /* clean up our vertice pointer array */ 
   if(graph_vertex_array) 
      {free(graph_vertex_array);}
   
   /* finally exit  */ 
   return(EXIT_SUCCESS);
}

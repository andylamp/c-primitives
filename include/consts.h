#ifndef _CONSTS_
    #define _CONSTS_
    
#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif   
 
#ifndef FAIL
    #define FAIL -1
#endif

#ifndef UNDEFINED
    #define UNDEFINED -2
#endif

#ifndef MAX_VERTEX_NAME_LEN
    #define MAX_VERTEX_NAME_LEN 10
#endif


#ifndef INITIAL_GRAPH_BUF_SIZE
    #define INITIAL_GRAPH_BUF_SIZE 16
#endif

#ifndef INITIAL_NEIGHBOR_BUF_SIZE
    #define INITIAL_NEIGHBOR_BUF_SIZE 4
#endif

/* debug flag if needed */
//#define DEBUG

/* handy debug macro */
#ifdef DEBUG
    #define dbg(x) {x} while(0)
#else
    #define dbg(x) {} while(0)
#endif

/* our vertex struct */
typedef struct _gsvertex {
    int visited;                        // is the vertex visited?
    int index;                          // vertex array index
    int vneighbor_num;                  // number of neighbors
    int allocated;                      // allocated neighbors
    char vname[MAX_VERTEX_NAME_LEN];    // vertex name
    //struct _gvertex *adj_list;          // the adjacency list
    struct _vneighbor *vneighbors;      // the adjacency list
} gsvertex;

/* structure to contain the neighbor vertices */
typedef struct _vneighbor {
    gsvertex *vpointer;
    int dist;
} vneighbor;

/* our graph struct */
typedef struct _pgraph {
    int vert_num;           // number of vertices
    int allocated;          // number of pre-allocated slots
    int *vdist;             // vertex distances
    int *vprev;             // previous hop node
    gsvertex **vertices;    // graph vertices
} pgraph;

#endif /* _CONSTS_ */

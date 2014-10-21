CC = cc
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE

DEBUG ?= 0
ifeq ($(DEBUG),1)
    CFLAGS += -g
else
    CFLAGS += -O3
endif

INLUDEDIR= -I./include/
GRAPHDIR=./graphs
QUEUESDIR=./queues
LISTSDIR=./lists

TESTSDIR=./tests

all: pq.o test_pqueue ll.o test_linkedlist graph.o test_graph dmst

pq.o: $(QUEUESDIR)/pqueue.c
		$(CC) $(CFLAGS) -o pq.o -c $(QUEUESDIR)/pqueue.c $(INLUDEDIR)

graph.o: $(GRAPHDIR)/graph.c
		$(CC) $(CFLAGS) -o graph.o -c $(GRAPHDIR)/graph.c $(INLUDEDIR)
		
graph_search.o: $(GRAPHDIR)/graph_search.c
		$(CC) $(CFLAGS)  -o graph_search.o -c $(GRAPHDIR)/graph_search.c $(INLUDEDIR)

test_graph: $(TESTSDIR)/test_graph.c
		$(CC) $(CFLAGS) $(TESTSDIR)/test_graph.c graph.o -o test_graph $(INLUDEDIR)

test_pqueue: $(TESTSDIR)/test_pqueue.c pq.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_pqueue.c pq.o -o test_pqueue $(INLUDEDIR)
		
ll.o: $(LISTSDIR)/linkedlist.c
		$(CC) $(CFLAGS) -o ll.o -c $(LISTSDIR)/linkedlist.c $(INLUDEDIR)
		
test_linkedlist: $(TESTSDIR)/test_linkedlist.c ll.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_linkedlist.c ll.o -o test_linkedlist $(INLUDEDIR)

test_dijkstra: $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o -o test_dijkstra $(INLUDEDIR)
		
clean:
		rm -rf  *~ ~* *.c~ *.h~ *.o~ *.o *.core test_dijkstra test_pqueue test_graph test_linkedlist
    

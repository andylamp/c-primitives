CC = cc
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE

DEBUG ?= 0
ifeq ($(DEBUG),1)
    CFLAGS += -g
else
    CFLAGS += -O3
endif

INLUDEDIR=./include/
INLUDES= -I$(INLUDEDIR)
GRAPHDIR=./graphs
QUEUESDIR=./queues
LISTSDIR=./lists

TESTSDIR=./tests

all: pq.o test_pqueue ll.o test_linkedlist graph.o test_graph test_dijkstra

pq.o: $(QUEUESDIR)/pqueue.c
		$(CC) $(CFLAGS) -o pq.o -c $(QUEUESDIR)/pqueue.c $(INLUDES)

graph.o: $(GRAPHDIR)/graph.c
		$(CC) $(CFLAGS) -o graph.o -c $(GRAPHDIR)/graph.c $(INLUDES)
		
graph_search.o: $(GRAPHDIR)/graph_search.c
		$(CC) $(CFLAGS)  -o graph_search.o -c $(GRAPHDIR)/graph_search.c $(INLUDES)

test_graph: $(TESTSDIR)/test_graph.c
		$(CC) $(CFLAGS) $(TESTSDIR)/test_graph.c graph.o -o test_graph $(INLUDES)

test_pqueue: $(TESTSDIR)/test_pqueue.c pq.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_pqueue.c pq.o -o test_pqueue $(INLUDES)
		
ll.o: $(LISTSDIR)/linkedlist.c
		$(CC) $(CFLAGS) -o ll.o -c $(LISTSDIR)/linkedlist.c $(INLUDES)
		
test_linkedlist: $(TESTSDIR)/test_linkedlist.c ll.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_linkedlist.c ll.o -o test_linkedlist $(INLUDES)

test_dijkstra: $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o -o test_dijkstra $(INLUDES)
		
clean:
		rm -rf  *~ ~* *.c~ *.h~ *.o~ *.o *.core \
		    $(INLUDEDIR)*~ $(INLUDEDIR)~* \
		    $(GRAPHDIR)/*~ $(GRAPHDIR)/~* \
		    $(QUEUESDIR)/*~ $(QUEUESDIR)/~* \
		    $(LISTSDIR)/*~ $(LISTSDIR)/~* \
		    $(TESTSDIR)/*~ $(TESTSDIR)/~* \
		    test_dijkstra test_pqueue test_graph test_linkedlist
    

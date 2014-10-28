CC = cc
CFLAGS = -Wall -std=c99 -D_GNU_SOURCE

DEBUG ?= 0
ifeq ($(DEBUG),1)
    CFLAGS += -g
else
    CFLAGS += -O3
endif

INCLUDEDIR=./include/
INCLUDES= -I$(INCLUDEDIR)
GRAPHDIR=./graphs
QUEUESDIR=./queues
LISTSDIR=./lists
HEAPSDIR=./heaps

TESTSDIR=./tests

all: pq.o test_pqueue ll.o lld.o lldc.o test_linkedlist test_linkedlistd test_linkedlistdc graph.o test_graph test_dijkstra fibheap.o

pq.o: $(QUEUESDIR)/pqueue.c
		$(CC) $(CFLAGS) -o pq.o -c $(QUEUESDIR)/pqueue.c $(INCLUDES)

graph.o: $(GRAPHDIR)/graph.c
		$(CC) $(CFLAGS) -o graph.o -c $(GRAPHDIR)/graph.c $(INCLUDES)
		
graph_search.o: $(GRAPHDIR)/graph_search.c
		$(CC) $(CFLAGS)  -o graph_search.o -c $(GRAPHDIR)/graph_search.c $(INCLUDES)

test_graph: $(TESTSDIR)/test_graph.c
		$(CC) $(CFLAGS) $(TESTSDIR)/test_graph.c graph.o -o test_graph $(INCLUDES)

test_pqueue: $(TESTSDIR)/test_pqueue.c pq.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_pqueue.c pq.o -o test_pqueue $(INCLUDES)
		
ll.o: $(LISTSDIR)/linkedlist.c
		$(CC) $(CFLAGS) -o ll.o -c $(LISTSDIR)/linkedlist.c $(INCLUDES)
		
test_linkedlist: $(TESTSDIR)/test_linkedlist.c ll.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_linkedlist.c ll.o -o test_linkedlist $(INCLUDES)

lld.o: $(LISTSDIR)/linkedlistd.c
		$(CC) $(CFLAGS) -c $(LISTSDIR)/linkedlistd.c -o lld.o $(INCLUDES)

test_linkedlistd: $(TESTSDIR)/test_linkedlistd.c lld.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_linkedlistd.c lld.o -o test_linkedlistd $(INCLUDES)

lldc.o: $(LISTSDIR)/linkedlistdc.c
		$(CC) $(CFLAGS) -c $(LISTSDIR)/linkedlistdc.c -o lldc.o $(INCLUDES)

test_linkedlistdc: $(TESTSDIR)/test_linkedlistdc.c lldc.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_linkedlistdc.c lldc.o -o test_linkedlistdc $(INCLUDES)

fibheap.o: $(HEAPSDIR)/fibheap.c
		$(CC) $(CFLAGS) -c $(HEAPSDIR)/fibheap.c -o fibheap.o $(INCLUDES)

test_dijkstra: $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o
		$(CC) $(CFLAGS) $(TESTSDIR)/test_dijkstra.c pq.o graph.o graph_search.o -o test_dijkstra $(INCLUDES)
		
clean:
		rm -rf  *~ ~* *.c~ *.h~ *.o~ *.o *.core \
		    $(INCLUDEDIR)*~ $(INCLUDEDIR)~* \
		    $(GRAPHDIR)/*~ $(GRAPHDIR)/~* \
		    $(QUEUESDIR)/*~ $(QUEUESDIR)/~* \
		    $(LISTSDIR)/*~ $(LISTSDIR)/~* \
	        $(HEAPSDIR)/*~ $(HEAPSDIR)/~* \
		    $(TESTSDIR)/*~ $(TESTSDIR)/~* \
		    test_dijkstra test_pqueue test_graph test_linkedlist test_linkedlistd test_linkedlistdc
    

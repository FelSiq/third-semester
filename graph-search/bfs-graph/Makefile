CCFLAGS = -I./include -std=c99 -Wall
CC = gcc
PROGRAM = bfs

all: queue.o graph.o main.o
	$(CC) queue.o graph.o main.o -o $(PROGRAM) $(CCFLAGS)
	rm *.o
queue.o:
	$(CC) -c ./src/queue.c $(CCFLAGS)
graph.o:
	$(CC) -c ./src/graph.c $(CCFLAGS)
main.o:
	$(CC) -c ./src/main.c $(CCFLAGS)
run:
	./$(PROGRAM)
clean:
	rm *.o
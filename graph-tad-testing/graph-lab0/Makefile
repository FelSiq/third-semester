CCFLAGS = -I./include -std=c99 -Wall
CC = gcc
PROGRAM = graph

all: list.o graph.o main.o
	$(CC) list.o graph.o main.o -o $(PROGRAM) $(CCFLAGS)
	rm *.o
list.o:
	$(CC) -c ./src/list.c $(CCFLAGS)
graph.o:
	$(CC) -c ./src/graph.c $(CCFLAGS)
main.o:
	$(CC) -c ./src/main.c $(CCFLAGS)
run:
	./$(PROGRAM)
clean:
	rm *.o
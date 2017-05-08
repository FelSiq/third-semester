CCFLAGS = -I./include -std=c99 -Wall
CC = gcc
PROGRAM = dfs

all: stack.o graph.o main.o
	$(CC) stack.o graph.o main.o -o $(PROGRAM) $(CCFLAGS)
	rm *.o
stack.o:
	$(CC) -c ./src/stack.c $(CCFLAGS)
graph.o:
	$(CC) -c ./src/graph.c $(CCFLAGS)
main.o:
	$(CC) -c ./src/main.c $(CCFLAGS)
run:
	./$(PROGRAM)
clean:
	rm *.o
CCFLAGS = -Wall -I./include
PROGNAME = graphs
CC = gcc

all: graph.o main.o
	$(CC) graph.o main.o $(CCFLAGS) -o $(PROGNAME)
	rm *.o
graph.o:
	$(CC) -c ./src/graph.c $(CCFLAGS)
main.o:
	$(CC) -c ./src/main.c $(CCFLAGS)
clean:
	rm *.o
cleanall: clean 
	rm $(PROGNAME)
run:
	./$(PROGNAME)
CCFLAGS = -std=c99 -I./include -Wall
all: dados.o main.o
	gcc dados.o main.o -o dados $(CCFLAGS)
	rm *.o
dados.o:
	gcc -c ./src/dados.c $(CCFLAGS)
main.o:
	gcc -c ./src/main.c $(CCFLAGS)
clean:
	rm *.o
run:
	./dados
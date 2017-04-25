CC = gcc
CFLAGS = -Wall -I./include
PROGNAM = coseqProcces

all: coseq main
	$(CC) cosequential.o main.o -o $(PROGNAM) $(CFLAGS)
	rm -r *.o
coseq:
	$(CC) -c ./src/cosequential.c $(CFLAGS)
main:
	$(CC) -c ./src/main.c $(CFLAGS)
clean:
	rm -r *.o $(PROGNAM)
run:
	./$(PROGNAM)
zip:
	zip -r ./package.zip ./*
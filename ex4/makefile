.PHONY: all clean

all: digitcompress

digitcompress: encodemain.o compress.a
	gcc -Wall -o digitcompress encodemain.o ./compress.a

encodemain.o: encodemain.c compress.h
	gcc -Wall -c encodemain.c -o encodemain.o

compress.o: compress.c compress.h
	gcc -Wall -c compress.c

compress.a: compress.o compress.h
	ar rcs compress.a compress.o
	ranlib compress.a

clean:
	rm -f *.o digitcompress compress.a
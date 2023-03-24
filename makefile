all:
	make compile
clean:
	rm -rf client server client.o a.out server.o common.o

compile:
	gcc -Wall ./main.c -o main

run:
	./main
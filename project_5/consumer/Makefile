CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: buffer.o consumer.o
	$(CC) $(CFLAGS) -o example consumer.o buffer.o $(PTHREADS)

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c $(PTHREADS)

consumer.o: consumer.c
	$(CC) $(CFLAGS) -c consumer.c $(PTHREADS)

clean:
	rm -rf *.o
	rm -rf example
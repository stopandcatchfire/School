# Makefile
# AlphaDerby - Shared Memory (1-minimum)

CMD_DELETE = /bin/rm -f
CC = gcc
MODEL = -m32
CFLAGS = $(MODEL) -Wall
LFLAGS = $(MODEL)

LIBS = -lrt

# ---------------------------------------------------

all:	server runner client
	$(CMD_DELETE) *.o
	chmod 755 server runner client

clean:
	$(CMD_DELETE) *.o server runner client

# ---------------------------------------------------

server:	server.o common.o
	$(CC) $(LFLAGS) -o $@ server.o common.o $(LIBS)

runner: runner.o common.o
	$(CC) $(LFLAGS) -o $@ runner.o common.o $(LIBS)

client: client.o common.o
	$(CC) $(LFLAGS) -o $@ client.o common.o $(LIBS)


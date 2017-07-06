# Makefile for parent.c and child.c, with common.c

CMD_DELETE = /bin/rm -f
CC = gcc
MODEL = -m32
#CFLAGS = $(MODEL) -O1 -Wall
CFLAGS = $(MODEL) -Wall
LFLAGS = $(MODEL)

LIBS = -lrt

# ---------------------------------------------------

all:	parent child
	$(CMD_DELETE) *.o
	chmod 755 parent child

clean:
	$(CMD_DELETE) *.o parent child

# ---------------------------------------------------

parent:	parent.o common.o
	$(CC) $(LFLAGS) -o $@ parent.o common.o $(LIBS)

child:	child.o common.o
	$(CC) $(LFLAGS) -o $@ child.o common.o $(LIBS)


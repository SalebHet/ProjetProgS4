CC= gcc
CFLAGS= -std=c99 -Wall -Werror 
CPPFLAGS= 
LDFLAGS= 
VPATH= 
CPPFLAGS= 
LDLIBS=-lm
SOURCES=grid.c afficher.c main.c
OUTFILE= main
OBJS= grid.o afficher.o

all : libgrid.a $(OUTFILE)


libgrid.a : grid.o
	ar -cr libgrid.a grid.o

grid.o : grid.c grid.h
main.o : main.c afficher.h grid.h
afficher.o : afficher.c afficher.h grid.h

#test-2048: grid.o main.o afficher.o
$(OUTFILE):$(OBJS)
.PHONY: clean
clean:
	-rm -f libgrid.a *.o $(OUTFILE)

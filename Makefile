ridCC= gcc
CFLAGS= -Wall -Werror 
CPPFLAGS= 
LDFLAGS= 
VPATH= 
CPPFLAGS= 
LDLIBS=-lm
SOURCES=grid.c afficher.c main.c
OUTFILES= test-2048


all : libgrid.a $(OUTFILES)


libgrid.a : grid.o
	ar -cr libgrid.a grid.o

grid.o : grid.o grid.h
main.o : main.c afficher.h grid.h
afficher.o : afficher.c afficher.h grid.h

test-2048: $(SOURCES)

.PHONY: clean
clean:
	-rm -f libgrid.a *.o $(OUTFILES)

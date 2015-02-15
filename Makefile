ridCC= gcc
CFLAGS= -Wall -Werror 
CPPFLAGS= 
LDFLAGS= 
VPATH= 
CPPFLAGS= 
LDLIBS=
SOURCES=grid.c
OUTFILES=


all :libgrid.a


libgrid.a : grid.o
	ar -cr libgrid.a grid.o

grid.o:grid.o grid.h

.PHONY: clean
clean:
	-rm -f libgrid.a grid.o

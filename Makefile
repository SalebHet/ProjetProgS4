CC= gcc
CFLAGS= -Wall -Werror 
CPPFLAGS= 
LDFLAGS= 
VPATH= 
CPPFLAGS= 
LDLIBS=
SOURCES=grid.c
OUTFILES=


all :grid.a


grid.a : grid.o
	ar -cr grid.o

grid.o:grid.o grid.h

.PHONY: clean
clean:
	-rm -f grid.a grid.o

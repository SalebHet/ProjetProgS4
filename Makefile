#Makefile
#le compilateur
CC= gcc
#les flags de compilation
CFLAGS=-std=c99 -Wall -Werror -g

OUTFILE=test-rationnel

OBJS= grid.o

#LDLIBS=-lm


$(OUTFILE): $(OBJS)

grid.o: grid.c grid.h
clean: rm -f $(OBJS) $(OUTFILE)

#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3 -std=c++14 -I./Llibs/
PROG = OpenGLSkeleton

SRCS = $(SRCMAIN)

SRCMAIN =./src/main.cpp

LIBS = -lGL -lglfw

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 


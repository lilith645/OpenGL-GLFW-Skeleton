#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3 -std=c++14 -I./Llibs/
PROG = OpenGLSkeleton

SRCS = $(SRCMAIN)

SRCMAIN =./src/main.cpp ./src/GraphicsHandler.cpp ./src/LoadTexture.cpp

LIBS = -lGL -lglfw -lGLEW

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 


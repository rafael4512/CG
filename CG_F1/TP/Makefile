  # the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -O2 -g -Wall #-Ofast

  # the build target executable:
TARGET1 = generator.cpp figures.cpp Engine/tinyxml/tinyxml.cpp Engine/tinyxml/tinystr.cpp Engine/tinyxml/tinyxmlerror.cpp Engine/tinyxml/tinyxmlparser.cpp
TARGET2 = generator

all:
	$(CC)  $(TARGET1) $(CFLAGS) -o $(TARGET2) -lm

clean:
	$(RM) $(TARGET2)

plane:
	$(CC)  $(TARGET1) $(CFLAGS) -o $(TARGET2) -lm
	./generator plane 10 Engine/Figures/plane.3d

box:
	$(CC)  $(TARGET1) $(CFLAGS) -o $(TARGET2) -lm
	./generator box 3 3 3 10 10 10 Engine/Figures/box.3d

sphere:
	$(CC)  $(TARGET1) $(CFLAGS) -o $(TARGET2) -lm
	./generator sphere 1 100 100 Engine/Figures/sphere.3d

cone:
	$(CC)  $(TARGET1) $(CFLAGS) -o $(TARGET2) -lm
	./generator cone 1 3 100 100 Engine/Figures/cone.3d

help:
	./generator -h

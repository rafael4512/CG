  # the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CCFLAGS  = -O2 -g -Wall


  # the build target executable:
TARGET1 = generator.cpp figures.cpp patch.cpp Engine/tinyxml/tinyxml.cpp Engine/tinyxml/tinystr.cpp Engine/tinyxml/tinyxmlerror.cpp Engine/tinyxml/tinyxmlparser.cpp
TARGET2 = generator

install:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm

all:
	./generator plane 10 Engine/Figures/plane.3d
	./generator box 3 3 3 3 3 3 Engine/Figures/box.3d
	./generator sphere 1 50 50 Engine/Figures/sphere.3d
	./generator torus 1 0.4 0.1 100 100 Engine/Figures/torus.3d
	./generator cone 1 3 50 50 Engine/Figures/cone.3d
	./generator patch 10 teapot.patch Engine/Figures/patch.3d

clean:
	$(RM) $(TARGET2)

plane:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator plane 10 Engine/Figures/plane.3d

box:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator box 3 3 3 3 3 3 Engine/Figures/box.3d

sphere:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator sphere 1 50 50 Engine/Figures/sphere.3d

torus:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator torus 1.5 0.7 0.05 100 100 Engine/Figures/torus.3d

cone:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator cone 1 3 50 50 Engine/Figures/cone.3d

patch:
	$(CC)  $(TARGET1) $(CCFLAGS) -o $(TARGET2) -lm
	./generator patch 10 teapot.patch Engine/Figures/patch.3d


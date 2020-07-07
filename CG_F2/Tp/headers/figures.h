#ifndef __FIGURES_H__
#define __FIGURES_H__

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std; 


int newFigure(std::ofstream &file, int ntri);
int drawTriangle(std::ofstream &file,double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3);

int drawPlane(std::ofstream &file, double size);
int drawBox(std::ofstream &file, double x, double y, double z, int dX, int dZ, int dY, int argc);
int drawSphere(std::ofstream &file, double raio, double slice, double stack);
int drawCone(std::ofstream &file, double raio, double alt, int slice, int stack);
int drawTorus(std::ofstream &file, double raio, double largura, double alt, int slice, int stack);

#endif
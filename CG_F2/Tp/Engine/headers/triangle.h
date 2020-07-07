#ifndef __TRIANGULO_H__
#define __TRIANGULO_H__



struct Triangulo {
	float x1;
	float y1;
	float z1;

	float x2;
	float y2;
	float z2;

	float x3;
	float y3;
	float z3;

	Triangulo* prox;
};

int parseFig(const char* filename,struct Triangulo **figura);
Triangulo* initTriangulo();

#endif
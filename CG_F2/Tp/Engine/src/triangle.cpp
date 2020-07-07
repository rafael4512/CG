#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../headers/triangle.h"

using namespace std;



Triangulo* initTriangulo() {
	Triangulo* tmp = (Triangulo*)malloc(sizeof(Triangulo));
	tmp->x1 = tmp->y1 = tmp->z1 = tmp->x2 = tmp->y2 = tmp->z2 = tmp->x3 = tmp->y3 = tmp->z3 = 0;
	tmp->prox = NULL;
	return tmp;
}

int parseFig(const char* filename, struct Triangulo **figure){
	FILE * f = fopen(filename,"r");

	if (!f){//se for null
		cout << " Nao foi possivel abrir o ficheiro "<< filename <<"\n";
		return false;

	}
	int ntriangles = 0; //primeira linha
	fscanf(f, "%d\n", &ntriangles);


	Triangulo* tmp = initTriangulo();
	Triangulo* inicio = tmp;
	int i;
	for (i=0; i < ntriangles; i++) {
		int res = fscanf(f,
						 "%f %f %f %f %f %f %f %f %f\n",
						 &(tmp->x1), &(tmp->y1), &(tmp->z1),
						 &(tmp->x2), &(tmp->y2), &(tmp->z2),
						 &(tmp->x3), &(tmp->y3), &(tmp->z3));

		if (res != 9) break;

		tmp->prox = initTriangulo();
		tmp = tmp->prox;
	}

	fclose(f);

	if (i == ntriangles) {
		*figure = inicio;
	}
	else {
		free(tmp);
	}

	return i == ntriangles;
}
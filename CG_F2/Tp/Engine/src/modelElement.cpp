#include "../headers/modelElement.h"

#define deviation 0.075

extern string curdir;
ModelElement::ModelElement(string filename, float red, float green, float blue)
{
	this->r = red;
	this->g = green;
	this->b = blue;

	filename.resize(filename.size());
	string path(curdir);
	path.append("Figures/");
	path.append(filename.c_str());

	parseFig(path.c_str(), &figure);
}

void ModelElement::Apply()
{
	Triangulo *triangulo = figure;

	for (; triangulo != NULL; triangulo = triangulo->prox) {

		glColor3f(r+deviation, g+deviation, b+deviation);
		glVertex3f(triangulo->x1, triangulo->y1, triangulo->z1);

		glColor3f(r, g, b);
		glVertex3f(triangulo->x2, triangulo->y2, triangulo->z2);

		glColor3f(r-deviation, g-deviation, b-deviation);
		glVertex3f(triangulo->x3, triangulo->y3, triangulo->z3);
	}
} 
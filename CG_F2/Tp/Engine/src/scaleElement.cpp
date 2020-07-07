#include "../headers/scaleElement.h"



ScaleElement::ScaleElement(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void ScaleElement::Apply()
{

	glScalef(x,y,z);

} 
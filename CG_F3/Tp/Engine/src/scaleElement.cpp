#include "../headers/scaleElement.h"



ScaleElement::ScaleElement(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void ScaleElement::apply(float t, bool orb)
{

	glScalef(x,y,z);

} 
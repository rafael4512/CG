#include "../headers/translateElement.h"



TranslateElement::TranslateElement(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void TranslateElement::Apply()
{

	glTranslatef(x,y,z);

} 
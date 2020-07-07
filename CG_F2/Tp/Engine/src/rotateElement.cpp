#include "../headers/rotateElement.h"



RotateElement::RotateElement(double angle, double axisX, double axisY, double axisZ)
{
	this->angle = angle;
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
}


void RotateElement::Apply()
{

	glRotatef(angle,axisX,axisY,axisZ);

} 
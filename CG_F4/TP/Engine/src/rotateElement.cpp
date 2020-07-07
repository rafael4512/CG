#include "../headers/rotateElement.h"



RotateElement::RotateElement(float time, float angle, float axisX, float axisY, float axisZ)
{
	this->time = time;
	this->angle = angle;
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
}


void RotateElement::apply(float t, bool orb)
{
	if (this->time)
		this->angle = 360 / this->time * t;
	
	glRotatef(angle,axisX,axisY,axisZ);

} 
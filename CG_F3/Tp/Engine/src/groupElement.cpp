#include "../headers/groupElement.h"



void GroupElement::apply(float t, bool orb)
{
	glPushMatrix();

	for (auto child : children)
		child->apply(t, orb);		

	glPopMatrix();

} 


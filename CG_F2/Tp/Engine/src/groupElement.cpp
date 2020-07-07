#include "../headers/groupElement.h"



void GroupElement::Apply()
{

	glPushMatrix();

	for (auto child : children)
		child->Apply();

	glPopMatrix();

} 


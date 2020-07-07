#include "../headers/modelsElement.h"



void ModelsElement::Apply()
{
	glBegin(GL_TRIANGLES);

	for (auto child : children)
		child->Apply();

	glEnd();
} 
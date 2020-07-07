#include "../headers/modelsElement.h"



void ModelsElement::apply(float t, bool orb)
{

	for (auto child : children)
		child->apply(t, orb);

} 
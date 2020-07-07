#include "../headers/sceneElement.h"



void SceneElement::apply(float t, bool orb)
{

	for (auto child : children)
		child->apply(t, orb);

} 
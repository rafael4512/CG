#include "../headers/sceneElement.h"



void SceneElement::Apply()
{

	for (auto child : children)
		child->Apply();

} 
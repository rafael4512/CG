#include "../headers/containerElement.h"



void ContainerElement::addChild(shared_ptr<BaseElement> ceChild)
{
	children.push_back(ceChild);
} 

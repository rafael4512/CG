#ifndef __MODELELEMENT_H__
#define __MODELELEMENT_H__

#include <string>

#include "triangle.h"
#include "baseElement.h"

using namespace std; 



class ModelElement : public BaseElement {

	public:
		ModelElement(string filename, float red, float green, float blue);
		void Apply() override;

	private:
		Triangulo *figure;
		float r, g, b;
		
};


#endif

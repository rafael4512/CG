#ifndef __MODELELEMENT_H__
#define __MODELELEMENT_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include "baseElement.h"

using namespace std; 



class ModelElement : public BaseElement {

	public:
		ModelElement(string filename, float red, float green, float blue);
		int prepareModel(const char* filename);
		void apply(float t, bool orb) override;

	private:
		float r, g, b;
		GLuint vertexCount;
		GLuint buffers[1];
};


#endif

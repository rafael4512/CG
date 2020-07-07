#ifndef __MODELELEMENT_H__
#define __MODELELEMENT_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include </usr/local/Cellar/devil/1.8.0_1/include/IL/il.h>
#include <GLUT/glut.h>
#else
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include "baseElement.h"

using namespace std; 



class ModelElement : public BaseElement {

	public:
		ModelElement(string filename, const char *texFile, float r, float g, float b, float emisR, float emisG, float emisB, float ambiR, 
			float ambiB, float ambiG, float diffR, float diffG, float diffB, float specR, float specG, float specB, float shiny);
		int prepareModel(const char* filename);
		void apply(float t, bool orb) override;
		

	private:
		void loadTexture(std::string s);

		float color[4], cEmis[4], cAmbi[4], cDiff[4], cSpec[4];
		float shiny;
		GLuint vertexCount;
		GLuint vertices, normals, texCoords;
		GLuint texID;
		bool hasTex;
		
};


#endif

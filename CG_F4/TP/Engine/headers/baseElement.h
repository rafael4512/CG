#ifndef __BASEELEMENT_H__
#define __BASEELEMENT_H__

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <zconf.h>
#else
#include "../zconf.h"
#include "direct.h"
#include <GL/glut.h>
#endif


class BaseElement {

	public: 
		virtual void apply(float t, bool orb) = 0;

};


#endif
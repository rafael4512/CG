#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "baseElement.h"

extern bool orb, isPaused, t;
extern double speed;


namespace Camera {
	void placeCamera();
	
	void drawAxis(float length);

	void idle(double k);

	void specialDown(int key, int xx, int yy);
	
	void specialUp(int key, int xx, int yy);
	
	void keyDown(unsigned char key, int x, int y);
	
	void keyUp(unsigned char key, int x, int y);

	void resetKeys();
}

#endif
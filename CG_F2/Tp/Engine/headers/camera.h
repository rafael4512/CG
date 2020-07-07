#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "baseElement.h"


namespace Camera {
	void placeCamera();
	void keyboardIsPressed(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int xx, int yy);
	void drawAxis(float length);
}

#endif
#include "../headers/camera.h"

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

extern int nTriangles;
extern int nLines;
extern bool orb;

namespace Camera {

	float upx = 0;
	float upy = 1;
	float upz = 0;
	float px = -2000.0f;
	float py = 2000.0f;
	float pz = 2000.0f;
	float lx = 0.0f;
	float ly = 0.0f;
	float lz = 0.0f;
	int mode = 1;

	float dist = sqrt(powf((px - lx), 2) + powf((py - ly), 2) + powf((pz - lz), 2));

	float alfa = M_PI - atan((px-lx) / (pz-lz));
	float beta = -M_PI_2 + (atan(sqrt(powf((px - lx), 2) + powf((pz - lz), 2)) / (py - ly) ));

	char fpss[64];
	float fps, timebase, frame = 0;

	bool eixos = true;
	static double r = 1;

	#define KEY_MAX 20
	#define TIMEBASE 1000
	#define DELTABETA M_PI / 600
	#define DELTAALFA M_PI / 600

	void spherical2Cartesian() {

		px = lx - dist * cos(beta) * sin(alfa);
		py = ly + dist * sin(beta);
		pz = lz - dist * cos(beta) * cos(alfa);
	}

	char keys[KEY_MAX];

	void specialDown(int key, int xx, int yy) {
		if (key == GLUT_KEY_RIGHT) {
			key = 2;
			keys[key] = 1; //Key hit.
		}
		else if (key == GLUT_KEY_LEFT) {
			key = 3;
			keys[key] = 1; //Key hit.
		}
		else if (key == GLUT_KEY_UP) {
			key = 0;
			keys[key] = 1; //Key hit.
		}
		else if (key == GLUT_KEY_DOWN) {
			key = 1;
			keys[key] = 1; //Key hit.
		}
	}

	void specialUp(int key, int xx, int yy) {
		if (key == GLUT_KEY_RIGHT) {
			key = 2;
			keys[key] = 0; //Key released.
		}
		else if (key == GLUT_KEY_LEFT) {
			key = 3;
			keys[key] = 0; //Key released.
		}
		else if (key == GLUT_KEY_UP) {
			key = 0;
			keys[key] = 0; //Key released.
		}
		else if (key == GLUT_KEY_DOWN) {
			key = 1;
			keys[key] = 0; //Key released.
		}
	}

	void keyDown(unsigned char key, int x, int y) {
		if (key == 'w' || key == 'W') {
			key = 4;
			keys[key] = 1; //Key hit.
		}
		else if (key == 's' || key == 'S') {
			key = 5;
			keys[key] = 1; //Key hit.
		}
		else if (key == 'a' || key == 'A') {
			key = 6;
			keys[key] = 1; //Key hit.
		}
		else if (key == 'd' || key == 'D') {
			key = 7;
			keys[key] = 1; //Key hit.
		}
		else if (key == 'q' || key == 'Q') {
			key = 8;
			keys[key] = 1; //Key hit.
		}
		else if (key == 'z' || key == 'Z') {
			key = 9;
			keys[key] = 1; //Key hit.
		}
		else if (key == ',') {
			key = 10;
			keys[key] = 1; //Key hit.
		}
		else if (key == '.') {
			key = 11;
			keys[key] = 1; //Key hit.
		}
		else if (key == '-') {
			key = 12;
			keys[key] = 1; //Key hit.
		}
	}

	void keyUp(unsigned char key, int x, int y) {
		if (key == 'w' || key == 'W') {
			key = 4;
			keys[key] = 0; //Key hit.
		}
		else if (key == 's' || key == 'S') {
			key = 5;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'a' || key == 'A') {
			key = 6;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'd' || key == 'D') {
			key = 7;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'q' || key == 'Q') {
			key = 8;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'z' || key == 'Z') {
			key = 9;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'e' || key == 'E') {
			eixos = !eixos;
		}
		else if (key == ',') {
			key = 10;
			keys[key] = 0; //Key hit.
		}
		else if (key == '.') {
			key = 11;
			keys[key] = 0; //Key hit.
		}
		else if (key == '-') {
			key = 12;
			keys[key] = 0; //Key hit.
		}
		else if (key == 'o' || key == 'O') {
			orb = !orb;
		}
		else if (key == ' ' || key == 'P' || key == 'p' || key == '0') {
			isPaused = !isPaused;
		}
		else if (key == 'f' || key == 'F')
		{
			if (r != 1.0f) {
				r = 1.0f;
			}
			else
			{
				r = 5.0f;
			}
		}
		else if (key == '*' || key == '2')
		{
			speed *= 2.0f;
		}
		else if (key == '/' || key == '1')
		{
			speed /= 2.0f;
		}
		else if (key == 'r' || key == 'R')
		{
			speed = -speed;
		}
		else if (key == 'v' || key == 'V')
		{
			mode *= -1;

			beta *= -1;
			alfa *= -1;
		}
	}

	void resetKeys() {
		for (size_t i = 0; i < KEY_MAX; i++) keys[i] = 0;
	}

	void placeCamera() {
		
		glLoadIdentity();
		gluLookAt(
			px, py, pz,		// P Camera Position
			lx, ly, lz,		// L Look at point
			upx, upy, upz);	// Up vector

		//sprintf(fpss, "FPS = %f", fps);
		//sprintf(fpss, "FPS = %f, Triangles = %d", fps, nTriangles);
		if(orb)
			sprintf(fpss, "FPS = %f, Triangles = %d, Orbit Lines =  %d", fps, nTriangles, nLines);
		else
			sprintf(fpss, "FPS = %f, Triangles = %d, Orbit Lines =  %d", fps, nTriangles, 0);

		glutSetWindowTitle(fpss);
	}

	float deg2rad(float deg){
		return deg * M_PI / 180;
	}

	void idle(double k) {
		float kWASD = r * k * 0.4;
		float kLook = r * k * 0.1;

		timebase += k;
		frame++;
		if (timebase > TIMEBASE)
		{
			fps = TIMEBASE * frame / timebase;
			timebase = 0;
			frame = 0;
		}

		if (mode == 1)
		{
			float dx = lx - px;
			float dy = ly - py;
			float dz = lz - pz;

			float dl = sqrt(powf(dx, 2) + powf(dy, 2) + powf(dz, 2));

			dx /= dl;
			dy /= dl;
			dz /= dl;

			float rx = -dz;
			float ry = 0;
			float rz = dx;

			float rl = sqrt(powf(rx, 2) + powf(rz, 2));

			rx /= rl;
			rz /= rl;

			// Up
			if (keys[0] == 1) {
				beta += (kLook * DELTABETA);
				if (beta < M_PI_2)
				{
					lx = px - dist * cos(beta) * sin(alfa);
					ly = py + dist * sin(beta);
					lz = pz + dist * cos(beta) * cos(alfa);
				}
				else
				{
					beta = M_PI_2 - DELTABETA;
				}
			}
			// Down
			if (keys[1] == 1) {
				beta -= (kLook * DELTABETA);
				if (beta > -M_PI_2)
				{
					lx = px - dist * cos(beta) * sin(alfa);
					ly = py + dist * sin(beta);
					lz = pz + dist * cos(beta) * cos(alfa);
				}
				else
				{
					beta = -M_PI_2 + DELTABETA;
				}
			}
			// Right
			if (keys[2] == 1) {
				alfa += (kLook * DELTAALFA);
				lx = px - dist * sin(alfa) * cos(beta);
				lz = pz + dist * cos(alfa) * cos(beta);
			}
			// Left
			if (keys[3] == 1) {
				alfa -= (kLook * DELTAALFA);
				lx = px - dist * sin(alfa) * cos(beta);
				lz = pz + dist * cos(alfa) * cos(beta);
			}
			// w
			if (keys[4] == 1) {
				px += kWASD * dx;
				py += kWASD * dy;
				pz += kWASD * dz;
				lx += kWASD * dx;
				ly += kWASD * dy;
				lz += kWASD * dz;
			}
			// s
			if (keys[5] == 1) {
				px -= kWASD * dx;
				py -= kWASD * dy;
				pz -= kWASD * dz;
				lx -= kWASD * dx;
				ly -= kWASD * dy;
				lz -= kWASD * dz;
			}
			// a
			if (keys[6] == 1) {
				px -= kWASD * rx;
				pz -= kWASD * rz;
				lx -= kWASD * rx;
				lz -= kWASD * rz;
			}
			// d
			if (keys[7] == 1) {
				px += kWASD * rx;
				pz += kWASD * rz;
				lx += kWASD * rx;
				lz += kWASD * rz;
			}
			// q
			if (keys[8] == 1) {
				// Up = (dy * rz, -(dx * rz - rx * dz), - dy * rx)

				px -= kWASD / 2 * dy * rz;
				py -= kWASD / 2 * -1 * (dx * rz - rx * dz);
				pz -= kWASD / 2 * -1 * dy * rx;
				lx -= kWASD / 2 * dy * rz;
				ly -= kWASD / 2 * -1 * (dx * rz - rx * dz);
				lz -= kWASD / 2 * -1 * dy * rx;
			}
			// z
			if (keys[9] == 1) {
				px += kWASD / 2 * dy * rz;
				py += kWASD / 2 * -1 * (dx * rz - rx * dz);
				pz += kWASD / 2 * -1 * dy * rx;
				lx += kWASD / 2 * dy * rz;
				ly += kWASD / 2 * -1 * (dx * rz - rx * dz);
				lz += kWASD / 2 * -1 * dy * rx;
			}
		}
		else if (mode == -1)
		{
			// Up
			if (keys[0] == 1) {
				beta += (kLook * DELTABETA);
				if (beta >= M_PI_2)
				{
					beta = M_PI_2 - DELTABETA;
				}
			}
			// Down
			if (keys[1] == 1) {
				beta -= (kLook * DELTABETA);
				if (beta <= -M_PI_2)
				{
					beta = -M_PI_2 + DELTABETA;
				}
			}
			// Right
			if (keys[2] == 1) {
				alfa -= (kLook * DELTAALFA);
			}
			// Left
			if (keys[3] == 1) {
				alfa += (kLook * DELTAALFA);
			}

			// w
			if (keys[4] == 1) {
				dist -= 50 * kWASD;
				if (dist <= 1000)
				{
					dist = 1000;
				}	
			}
			// s
			if (keys[5] == 1) {
				dist += 50 * kWASD;
			}
			spherical2Cartesian();
		}

		// ,
		if (keys[10] == 1) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		// .
		if (keys[11] == 1) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}
		// -
		if (keys[12] == 1) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
			   
		glutPostRedisplay();
	}

	void drawAxis(float length){
		// put drawing instructions here
		if (eixos) {
			float axisC[] = {1,1,1,1};
			glMaterialfv(GL_FRONT, GL_EMISSION, axisC);
			glBegin(GL_LINES);
			// X axis in red
			glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-length, 0.0f, 0.0f); glVertex3f(length, 0.0f, 0.0f);
			// Y Axis in Green
			glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -length, 0.0f); glVertex3f(0.0f, length, 0.0f);
			// Z Axis in Blue
			glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -length); glVertex3f(0.0f, 0.0f, length);
			glEnd();
		}
	}
}
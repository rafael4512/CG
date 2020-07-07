#include "../headers/camera.h"

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

namespace Camera {

	float cx = 0;
	float cy = 0;
	float cz = 10;
	float px = 0.0f;
	float py = 0.0f;
	float pz = 0.0f;
	float alfa = 0.0f;
	float beta = 0.0f;
	float radius = cz;
	bool eixos = true;


	void placeCamera(){
		// set the camera
		glLoadIdentity();
			gluLookAt(
				cx, cy, cz,
				px, py, pz,
				0, 1, 0);
	}

	void spherical2CartesianFix() {
		px = cx + radius * cos(beta) * sin(alfa);
		py = cy + radius * sin(beta);
		pz = cz - radius * cos(beta) * cos(alfa);

	}

	float deg2rad(float deg){
		return deg * M_PI / 180;
	}

	void keyboardIsPressed(unsigned char key, int x, int y){
		switch (key){
			case 'q':
				// Andar para cima
				px += sin(-beta) * sin(alfa);
				py += cos(-beta);
				pz += sin(-beta) * cos(alfa);
				cx += sin(-beta) * sin(alfa);
				cy += cos(-beta);
				cz += sin(-beta) * cos(alfa);
				break;
			case 'z':
				// Andar para baixo
				px -= sin(-beta) * sin(alfa);
				py -= cos(-beta);
				pz -= sin(-beta) * cos(alfa);
				cx -= sin(-beta) * sin(alfa);
				cy -= cos(-beta);
				cz -= sin(-beta) * cos(alfa);
				break;
			case 'w':
				// Andar para frente
				px -= cos(-beta) * sin(-alfa);
				py -= sin(-beta);
				pz -= cos(-beta) * cos(-alfa);
				cx -= cos(-beta) * sin(-alfa);
				cy -= sin(-beta);
				cz -= cos(-beta) * cos(-alfa);
				break;
			case 's':
				// Andar para trás
				px += cos(-beta) * sin(-alfa);
				py += sin(-beta);
				pz += cos(-beta) * cos(-alfa);
				cx += cos(-beta) * sin(-alfa);
				cy += sin(-beta);
				cz += cos(-beta) * cos(-alfa);
				break;
			case 'a':
				// Andar para esquerda
				if (cos(beta) > 0) {
					px -= cos(alfa);
					pz -= sin(alfa);
					cx -= cos(alfa);
					cz -= sin(alfa);
				}
				else {
					px += cos(alfa);
					pz += sin(alfa);
					cx += cos(alfa);
					cz += sin(alfa);
				}
				break;
			case 'd':
				// Andar para direita
				if (cos(beta) > 0) {
					px += cos(alfa);
					pz += sin(alfa);
					cx += cos(alfa);
					cz += sin(alfa);
				}
				else {
					px -= cos(alfa);
					pz -= sin(alfa);
					cx -= cos(alfa);
					cz -= sin(alfa);
				}
				break;
			case 'e':
				eixos = !eixos;
				break;
			case '-':
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			case '.':
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				break;
			case ',':
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			default:
				break;
		}
		glutPostRedisplay();
	}

	void processSpecialKeys(int key, int xx, int yy) {
		switch (key) {
		case GLUT_KEY_RIGHT:
			alfa += M_PI / 30;
			spherical2CartesianFix();
			break;
		case GLUT_KEY_LEFT:
			alfa -= M_PI / 30;
			spherical2CartesianFix();
			break;
		case GLUT_KEY_UP:
			beta += M_PI / 30;
			if (beta >= 14 * M_PI / 30)
				beta = 14 * M_PI / 30;
			spherical2CartesianFix();
			break;
		case GLUT_KEY_DOWN:
			beta -= M_PI / 30;
			if (beta <= -14 * M_PI / 30)
				beta = -14 * M_PI / 30;
			spherical2CartesianFix();
			break;
		case GLUT_KEY_PAGE_UP:
			double difX, difY, difZ;
			difX = cx - (double) px;
			difY = cy - (double) py;
			difZ = cz - (double) pz;
			double r;
			r = sqrt(difX * difX + difY * difY + difZ * difZ);
			if (r >= 4) {
				cx -= 0.2 * cos(-beta) * sin(-alfa);
				cy -= 0.2 * sin(-beta);
				cz -= 0.2 * cos(-beta) * cos(-alfa);
			}
			break;
		case GLUT_KEY_PAGE_DOWN:
			cx += 0.2 * cos(-beta) * sin(-alfa);
			cy += 0.2 * sin(-beta);
			cz += 0.2 * cos(-beta) * cos(-alfa);
			break;
		default: break;
		}
		glutPostRedisplay();
	}

	void drawAxis(float length){
		// put drawing instructions here
		if (eixos) {
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
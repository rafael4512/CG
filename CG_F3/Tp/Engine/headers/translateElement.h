#ifndef __TRANSLATEELEMENT_H__
#define __TRANSLATEELEMENT_H__

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include "baseElement.h"

#define nCurvePoints 1000
extern float gtInc;

class TranslateElement : public BaseElement {

	public:
		TranslateElement(float time, float x, float y, float z);
		void addCoords(float x, float y, float z);
		void genCurveMatrix();
		void multMatrixVector(float* m, float* v, float* res);
		void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);
		void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv);
		void renderCatmullRomCurve();
		void apply(float t, bool orb) override;

	private:
		float x, y, z;
		float time;
		std::vector<float> curveCoords;
		float **curvePoints;
		float orbit[nCurvePoints][3];
		GLuint vertexCount, vertices;

};


#endif
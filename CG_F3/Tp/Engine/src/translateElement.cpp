#include "../headers/translateElement.h"
#include <iostream>

float gtInc = (float)1 / nCurvePoints;

TranslateElement::TranslateElement(float time, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->time = time;
}

void TranslateElement::addCoords(float x, float y, float z)
{
	this->curveCoords.push_back(x);
	this->curveCoords.push_back(y);
	this->curveCoords.push_back(z);
}

void TranslateElement::multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void TranslateElement::getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

	// catmull-rom matrix
	float M[16] = { -0.5f, 1.5f, -1.5f, 0.5f, 1.0f, -2.5f, 2.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

	float T[4] = { t * t * t , t * t , t , 1 };
	float dT[4] = { 3 * t * t , 2 * t , 1 , 0 };

	for (int i = 0; i < 3; i++)
	{
		float P[4];
		P[0] = p0[i];
		P[1] = p1[i];
		P[2] = p2[i];
		P[3] = p3[i];

		float A[4];
		// Compute A = M * P
		multMatrixVector(M, P, A);

		// Compute pos = T * A
		pos[i] = T[0] * A[0] + T[1] * A[1] + T[2] * A[2] + T[3] * A[3];

		// compute deriv = T' * A
		deriv[i] = dT[0] * A[0] + dT[1] * A[1] + dT[2] * A[2] + dT[3] * A[3];

	}
}


// given  global t, returns the point in the curve
void TranslateElement::getGlobalCatmullRomPoint(float gt, float* pos, float* deriv) {
	int PointCount = this->curveCoords.size() / 3;
	float t = gt * PointCount; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + PointCount - 1) % PointCount;
	indices[1] = (indices[0] + 1) % PointCount;
	indices[2] = (indices[1] + 1) % PointCount;
	indices[3] = (indices[2] + 1) % PointCount;

	getCatmullRomPoint(t, this->curvePoints[indices[0]], this->curvePoints[indices[1]], 
							this->curvePoints[indices[2]], this->curvePoints[indices[3]], pos, deriv);
}

void TranslateElement::genCurveMatrix()
{
	const int nPoints = this->curveCoords.size() / 3;
	int i;

	this->curvePoints = (float**)malloc(nPoints * sizeof(float*));
	for (i = 0; i < nPoints; i++)
		this->curvePoints[i] = (float*)malloc(3 * sizeof(float));

	for (i = 0; i < nPoints; i++)
	{
		this->curvePoints[i][0] = this->curveCoords[i * 3];
		this->curvePoints[i][1] = this->curveCoords[i * 3 + 1];
		this->curvePoints[i][2] = this->curveCoords[i * 3 + 2];
	}

	// Generate orbit matrix
	float deriv[3];
	float gt = 0;
	for (int i = 0; i < nCurvePoints; gt = gt + gtInc, i++)
		getGlobalCatmullRomPoint(gt, this->orbit[i], deriv);


	std::vector<float> orbitVBO;
	for (int i = 0; i < nCurvePoints; i++)
	{
		orbitVBO.push_back(orbit[i][0]);
		orbitVBO.push_back(orbit[i][1]);
		orbitVBO.push_back(orbit[i][2]);
	}
	this->vertexCount = orbitVBO.size() / 3;
	glGenBuffers(1, &(this->vertices));

	// copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * orbitVBO.size(), // tamanho do vector em bytes
		orbitVBO.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)

	glVertexPointer(3, GL_FLOAT, 0, 0);

}

void TranslateElement::renderCatmullRomCurve() 
{
	/*
	glBegin(GL_LINE_LOOP); //GL_POINTS
	for (int i = 0; i < nCurvePoints; i++)
		glVertex3f(this->orbit[i][0], this->orbit[i][1], this->orbit[i][2]);
	glEnd();
	*/

	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_LINE_LOOP, 0, this->vertexCount);

	
}


void TranslateElement::apply(float t, bool orb)
{
	if (this->time)
	{
        glColor3f(0.8, 0.8, 0.8);
		if (orb)
			renderCatmullRomCurve();

		t /= this->time;
		float xyz[3];
		float deriv[3];
		getGlobalCatmullRomPoint(t, xyz, deriv);

		glTranslatef(xyz[0], xyz[1], xyz[2]);
	}
	else
	{
		glTranslatef(this->x, this->y, this->z);
	}
} 
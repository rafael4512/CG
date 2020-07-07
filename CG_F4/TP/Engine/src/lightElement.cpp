#include "../headers/lightElement.h"


LightElement::LightElement(int id, string type, float x, float y, float z, float ambiR, float ambiB, float ambiG,
	float diffR, float diffG, float diffB, float specR, float specG, float specB, float spotX, float spotY, float spotZ,
	float cutoff, float exp, float attX, float attY, float attZ)
{
	glEnable(GL_LIGHTING);
	this->lightId = GL_LIGHT0 + id; //lights[id]

	this->cAmbi[0] = ambiR; this->cAmbi[1] = ambiG; this->cAmbi[2] = ambiB; this->cAmbi[3] = 1;
	this->cDiff[0] = diffR; this->cDiff[1] = diffG; this->cDiff[2] = diffB; this->cDiff[3] = 1;
	this->cSpec[0] = specR; this->cSpec[1] = specG; this->cSpec[2] = specB; this->cSpec[3] = 1;
	this->att[0] = attX; this->att[1] = attY; this->att[2] = attZ;

	this->pos[0] = x; this->pos[1] = y; this->pos[2] = z;
	this->cutoff = cutoff;

	if (type == "POINT")
		this->pos[3] = 1; // ponto
	else if (type == "DIRECTIONAL")
		this->pos[3] = 0; // vetor
	else if (type == "SPOT")
	{
		this->pos[3] = 1;
		this->spotDir[0] = 0; this->spotDir[1] = 0; this->spotDir[2] = -1;
		this->exp = exp;
	}

	glEnable(lightId);
}



void LightElement::apply(float t, bool orb)
{

	glLightfv(this->lightId, GL_POSITION, this->pos);
	
	if (this->cutoff != -1) //Cutoff not optional
	{
		glLightfv(this->lightId, GL_SPOT_DIRECTION, this->spotDir);
		glLightf(this->lightId, GL_SPOT_CUTOFF, this->cutoff); // [0,90] ou 180
		glLightf(this->lightId, GL_SPOT_EXPONENT, this->exp); // [0,128]

	}

	glLightfv(this->lightId, GL_CONSTANT_ATTENUATION, this->att);
	glLightfv(this->lightId, GL_AMBIENT, this->cAmbi);
	glLightfv(this->lightId, GL_DIFFUSE, this->cDiff);
	glLightfv(this->lightId, GL_SPECULAR, this->cSpec);

} 



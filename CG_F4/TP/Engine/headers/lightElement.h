#ifndef __LIGHTELEMENT_H__
#define __LIGHTELEMENT_H__

#include <string>

#include "containerElement.h"
#include "baseElement.h"



class LightElement : public ContainerElement {

	public:
		LightElement(int id, string type, float x, float y, float z, float ambiR, float ambiB, float ambiG, float diffR, float diffG, 
			float diffB, float specR, float specG, float specB, float spotX, float spotY, float spotZ, float cutoff, float exp, 
			float attX, float attY, float attZ);
		void apply(float t, bool orb) override;
	
	private:
		int lightId;
		float pos[4], cAmbi[4], cDiff[4], cSpec[4];
		float spotDir[3]; float cutoff; float exp;
		float att[3];

};


#endif
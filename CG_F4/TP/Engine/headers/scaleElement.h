#ifndef __SCALEELEMENT_H__
#define __SCALEELEMENT_H__

#include "baseElement.h"



class ScaleElement : public BaseElement {

	public:
		ScaleElement(float x, float y, float z);
		void apply(float t, bool orb) override;

	private:
		float x, y, z;

};


#endif
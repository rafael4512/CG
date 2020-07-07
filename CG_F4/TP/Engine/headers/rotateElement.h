#ifndef __ROTATEELEMENT_H__
#define __ROTATEELEMENT_H__

#include "baseElement.h"



class RotateElement : public BaseElement {

	public:
		RotateElement(float time, float angle, float axisX, float axisY, float axisZ);
		void apply(float t, bool orb) override;

	private:
		float angle, axisX, axisY, axisZ;
		float time;

};


#endif
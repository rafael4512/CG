#ifndef __ROTATEELEMENT_H__
#define __ROTATEELEMENT_H__

#include "baseElement.h"



class RotateElement : public BaseElement {

	public:
		RotateElement(double angle, double axisX, double axisY, double axisZ);
		void Apply() override;

	private:
		double angle, axisX, axisY, axisZ;

};


#endif
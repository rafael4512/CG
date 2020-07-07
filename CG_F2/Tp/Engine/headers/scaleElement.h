#ifndef __SCALEELEMENT_H__
#define __SCALEELEMENT_H__

#include "baseElement.h"



class ScaleElement : public BaseElement {

	public:
		ScaleElement(double x, double y, double z);
		void Apply() override;

	private:
		double x, y, z;

};


#endif
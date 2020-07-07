#ifndef __TRANSLATEELEMENT_H__
#define __TRANSLATEELEMENT_H__

#include "baseElement.h"



class TranslateElement : public BaseElement {

	public:
		TranslateElement(double xx, double yy, double zz);
		void Apply() override;

	private:
		double x, y, z;

};


#endif
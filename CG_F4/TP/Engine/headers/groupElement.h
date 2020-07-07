#ifndef __GROUPELEMENT_H__
#define __GROUPELEMENT_H__

#include "containerElement.h"
#include "baseElement.h"



class GroupElement : public ContainerElement {

	public:
		void apply(float t, bool orb) override;

};


#endif
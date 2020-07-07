#ifndef __MODELSELEMENT_H__
#define __MODELSELEMENT_H__

#include "containerElement.h"
#include "baseElement.h"



class ModelsElement : public ContainerElement {

	public:
		void apply(float t, bool orb) override;
		
};


#endif
#ifndef __SCENEELEMENT_H__
#define __SCENEELEMENT_H__

#include "containerElement.h"
#include "baseElement.h"



class SceneElement : public ContainerElement {

	public:
		void apply(float t, bool orb) override;

};


#endif
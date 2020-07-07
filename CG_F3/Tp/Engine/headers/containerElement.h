#ifndef __CONTAINERELEMENT_H__
#define __CONTAINERELEMENT_H__

#include <vector>
#include <memory>

#include "baseElement.h"

using namespace std;



class ContainerElement : public BaseElement {

	public:
		void addChild(shared_ptr<BaseElement> ceChild);


	protected:
		vector< shared_ptr<BaseElement> > children;
	
};


#endif
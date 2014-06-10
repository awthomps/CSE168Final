#ifndef CSE168_WOOD_H
#define CSE168_WOOD_H

#include "ProceduralTexture.h"

class Wood : public ProceduralTexture {
public:


private:
	float SampleFunction(float s, float t, float r) {
		return ((s - origin.x)*(s)-origin.x) + ((t - origin.y)*(t - origin.y));
	}

};






#endif
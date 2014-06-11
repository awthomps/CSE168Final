#ifndef CSE168_WOOD_H
#define CSE168_WOOD_H

#include "ProceduralTexture.h"

class Wood : public ProceduralTexture {
public:
	Wood() :ProceduralTexture() {
		unsigned int size = 2;
		Color colors[2];
		colors[0] = Color(Vector3(139.0 / 255.0, 69.0 / 255.0, 29.0 / 255.0)/2.0);
		colors[1] = Color(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
		SetColorMap(size, colors);
	}

private:
	float SampleFunction(float s, float t, float r) {
		if (orientation == ORIENTATION_X) {
			return (((t - origin.y)*(t - origin.y)) + ((r - origin.z)*(r - origin.z)))+SampleNoise(s, t, r);
		}
		else if (orientation == ORIENTATION_Y) {
			return (((s - origin.x)*(s - origin.x)) + ((r - origin.z)*(r - origin.z))) +SampleNoise(s, t, r);
		}
		else {
			return (((s - origin.x)*(s - origin.x)) + ((t - origin.y)*(t - origin.y))) +SampleNoise(s, t, r);
		}
	}


};






#endif
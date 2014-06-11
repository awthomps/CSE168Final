#ifndef CSE168_CARPET_H
#define CSE168_CARPET_H

#include "ProceduralTexture.h"


class Carpet : public ProceduralTexture {
public:
	Carpet() : ProceduralTexture() {

		unsigned int size = 3;
		Color colors[3];
		colors[0] = Color(.04, .3, .02);
		colors[1] = Color(.5, .2, .5);
		colors[2] = Color(1.0, 0.2, 0.1);
		SetColorMap(size, colors);
	}

	Color ColorFromMap(float val) {
		if (val < 0.333) {
			return ColorMap[0];
		}
		else if (val < 0.5) {
			return ColorMap[1];
		}
		else return ColorMap[2];
	}


private:
	float SampleFunction(float s, float t, float r) {
		return SampleNoise(s - origin.x , t - origin.y, r - origin.z);
	}
};


#endif
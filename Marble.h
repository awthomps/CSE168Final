
#ifndef CSE168_MARBLE_H
#define CSE168_MARBLE_H

#include "ProceduralTexture.h"

class Marble : public ProceduralTexture {
public:
	Marble() : ProceduralTexture() {

		unsigned int size = 2;
		Color colors[2];
		colors[0] = Color(Vector3(.2, .2, .2));
		colors[1] = Color(Vector3(1, 1, 1));
		SetColorMap(size, colors);
	}

	Color ColorFromMap(float val) {
		if (val < .1666) {
			return ColorMap[0];
		}
		else if (val < .3333) {
			return ColorMap[1];
		}
		else if (val < .5) {
			return ColorMap[0];
		}
		else if (val < .6666) {
			return ColorMap[1];
		}
		else if (val < 0.8333) {
			return ColorMap[0];
		}
		else return ColorMap[1];
	}


private:
	float SampleFunction(float s, float t, float r) {
		float accum = 0.0;

		for (int i = 1; i < 4; ++i) {
			accum += pow(2.0, -i) * SampleNoise(pow(2.0, i)*s, pow(2.0, i)*t, pow(2.0, i)*r);
		}
		if (orientation == ORIENTATION_X) {
			accum += s;
		}
		else if (orientation == ORIENTATION_Y) {
			accum += t;
		}
		else {
			accum += r;
		}

		return sin(PI * accum);
	}
};

#endif
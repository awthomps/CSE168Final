
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

		/*
		unsigned int size = 7;
		Color colors[7];
		colors[0] = Color(Vector3(0, 0, 0));
		colors[1] = Color(Vector3(0.5, 0.5, 0.5));
		colors[2] = Color(Vector3(0.75, 0.75, 0.75));
		colors[3] = Color(Vector3(1, 1, 1));
		colors[4] = Color(Vector3(0.75, 0.75, 0.75));
		colors[5] = Color(Vector3(0.5, 0.5, 0.5));
		colors[6] = Color(Vector3(0, 0, 0));
		*/
		SetColorMap(size, colors);
	}

	Color ColorFromMap(float val) {
		if (val < 0.5) {
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
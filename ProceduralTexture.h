#ifndef CSE168_PROCEDURALTEXTURE_H
#define CSE168_PROCEDURALTEXTURE_H

#include "Material.h";
#include "Vector3.h";
#include "Intersection.h"
#include "Color.h";
#include <random>;
#include <cmath>;

#define SIZE_OF_NOISE 50

class ProceduralTexture : public Material {
public:
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) = 0;
	virtual void GenerateSample(Color &color, Vector3 &sample, const Vector3 &in, const Intersection &hit) = 0;
	void SetOrigin(Vector3 orig) { origin = orig; }

protected:
	float noise[SIZE_OF_NOISE][SIZE_OF_NOISE][SIZE_OF_NOISE];
	Vector3 origin;
	Color *ColorMap;
	unsigned int MapSize;

	void SetColorMap(unsigned int size, Color *colors) {
		MapSize = size;
		if (ColorMap) delete []ColorMap;
		ColorMap = new Color[MapSize];
		for (unsigned int i = 0; i < MapSize; ++i) {
			ColorMap[i] = colors[i];
		}
	}

	Color ColorFromMap(float val) {
		//lerp color
		if (MapSize <= 0) return Color(0.0f, 0.0f, 0.0f);
		else if (MapSize == 1) return *ColorMap;

		float SampleLocation = ((float)MapSize) * val;
		unsigned int top = ceil(SampleLocation);
		unsigned int bot = floor(SampleLocation);
		float diff = ((float)SampleLocation) - bot;

		Vector3 retCol, topCol = ColorMap[top].getInVector3(), botCol = ColorMap[bot].getInVector3();
		for (unsigned int i = 0; i < 3; ++i){
			if (topCol[i] > botCol[i]) retCol[i] = (diff * (topCol[i] - botCol[i])) + botCol[i];
			else ((1 - diff) * (botCol[i] - topCol[i])) + topCol[i];
		}
		return Color(retCol);
	}


	float SampleFunction(Vector3 samplePt) { return SampleFunction(samplePt.x, samplePt.y, samplePt.z); }
	virtual float SampleFunction(float s, float t, float r);


	void GenerateNoise() {
		//generate noise:
		for (unsigned int r = 0; r < SIZE_OF_NOISE; ++r) {
			for (unsigned int t = 0; t < SIZE_OF_NOISE; ++t) {
				for (unsigned int s = 0; s < SIZE_OF_NOISE; ++s) {
					noise[r][t][s] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
			}
		}
	}

private:
};



#endif
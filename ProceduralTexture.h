#ifndef CSE168_PROCEDURALTEXTURE_H
#define CSE168_PROCEDURALTEXTURE_H

#include "Material.h";
#include "Vector3.h";
#include "Intersection.h"
#include "Color.h";
#include "Matrix34.h";
#include <random>;
#include <cmath>;
#include <iostream>;

#define SIZE_OF_NOISE 50
#define ORIENTATION_X 0
#define ORIENTATION_Y 1
#define ORIENTATION_Z 2

class ProceduralTexture : public Material {
public:
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) = 0;
	virtual void GenerateSample(Color &color, Vector3 &sample, const Vector3 &in, const Intersection &hit) = 0;
	void SetOrigin(Vector3 orig) { origin = orig; }
	virtual Color GenerateColor(Vector3 v)=0;
	void SetScale(float s){ scale = s; }
	void SetOrientation(unsigned orient) { orientation = orient;  }

protected:
	float noise[SIZE_OF_NOISE][SIZE_OF_NOISE][SIZE_OF_NOISE];
	float scale;
	Vector3 origin;
	Color *ColorMap;
	unsigned int MapSize;
	unsigned int orientation;

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

		float SampleLocation = val / ((float)MapSize);
		//std::cout << val << std::endl;
		unsigned int top = ceil(SampleLocation);
		unsigned int bot = floor(SampleLocation);
		float diff = SampleLocation - bot;
		//std::cout << "Diff: " << diff << std::endl;

		Color ret;
		ret.FromLinearInterpolation(ColorMap[bot], ColorMap[top], val);
		//ret.getInVector3().Print("Color");
		return ret;
		/*
		Vector3 retCol, topCol = ColorMap[top].getInVector3(), botCol = ColorMap[bot].getInVector3();
		for (unsigned int i = 0; i < 3; ++i){
			if (topCol[i] > botCol[i]) retCol[i] = (diff * (topCol[i] - botCol[i])) + botCol[i];
			else retCol[i] = ((1.0 - diff) * (botCol[i] - topCol[i])) + topCol[i];
		}
		//topCol.Print("BrighthColor: ");
		//botCol.Print("DarkColor: ");
		//retCol.Print("Color: ");
		return Color(retCol);*/
	}


	virtual float SampleFunction(float s, float t, float r)=0;


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
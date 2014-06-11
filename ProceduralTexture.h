#ifndef CSE168_PROCEDURALTEXTURE_H
#define CSE168_PROCEDURALTEXTURE_H

#include "Material.h";
#include "Vector3.h";
#include "Intersection.h"
#include "Color.h";
#include "Matrix34.h";
#include "Core.h";
#include <random>;
#include <cmath>;
#include <iostream>;

#define SIZE_OF_NOISE 10
#define ORIENTATION_X 0
#define ORIENTATION_Y 1
#define ORIENTATION_Z 2

class ProceduralTexture : public Material {
public:
	ProceduralTexture() {
		scale = 1.0f;
		orientation = ORIENTATION_X;
		noiseDistance = 1.0f;
		GenerateNoise();
		amp = 1.0f;
		for (unsigned int i = 0; i < 3; ++i) {
			phase[i] = 0.0f;
			freq[i] = 1.0f;
		}
	}

	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) = 0;
	virtual void GenerateSample(Color &color, Vector3 &sample, const Vector3 &in, const Intersection &hit) = 0;
	void SetOrigin(Vector3 orig) { origin = orig; }
	virtual Color GenerateColor(Vector3 v)=0;
	void SetScale(float s){ scale = s; }
	void SetOrientation(unsigned orient) { orientation = orient;  }
	void SetNoiseDistance(float dist) { noiseDistance = dist; }
	void SetNoiseBehavior(float ps, float pt, float pr, float amplitudeN, float fsN, float ftN, float frN){
		phase[0] = ps; phase[1] = pt; phase[2] = pr; amp = amplitudeN; freq[0] = fsN; freq[1] = ftN; freq[2] = frN;
	}

protected:
	float noise[SIZE_OF_NOISE][SIZE_OF_NOISE][SIZE_OF_NOISE];
	float scale, noiseDistance;
	float phase[3], amp, freq[3]; //frequencies;
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

	float SampleNoise(float s, float t, float r) {
		float sF = (s * freq[0]) + phase[0];
		sF /= noiseDistance;
		float tF = (t * freq[1]) + phase[1];
		tF /= noiseDistance;
		float rF = (r * freq[2]) + phase[2];
		rF /= noiseDistance;

		int sPos = floor((SIZE_OF_NOISE - 1) * sF);
		int tPos = floor((SIZE_OF_NOISE-1) * tF);
		int rPos = floor((SIZE_OF_NOISE-1) * rF);

		float diffS, diffT, diffR;
		diffS = ((SIZE_OF_NOISE - 1) * sF) - ((float)sPos);
		diffT = ((SIZE_OF_NOISE - 1) * tF) - ((float)tPos);
		diffR = ((SIZE_OF_NOISE - 1) * rF) - ((float)rPos);

		if (sF < 0.0f) {
			diffS = 1.0 - diffS;
			sPos = SIZE_OF_NOISE - 1 - sPos;
		}
		if (tF < 0.0f) {
			diffT = 1.0 - diffT;
			tPos = SIZE_OF_NOISE - 1 - tPos;
		}
		if (rF < 0.0f) {
			diffR = 1.0 - diffR;
			rPos = SIZE_OF_NOISE - 1 - rPos;
		}


		//work the "noiseDistance" into this
		
		//Y planes:
		float valBot = yPlaneInterpolation(sPos, tPos, rPos, diffS, diffR);
		float valTop = yPlaneInterpolation(sPos, tPos + 1, rPos, diffS, diffR);
		return amp * Linear(valBot, valTop, diffT);
	}

private:

	float yPlaneInterpolation(int xLow, int yLevel, int zLow, float xt, float zt) {
		float lowB, highB, lowT, highT;
		lowB = noise[(zLow)%SIZE_OF_NOISE][yLevel%SIZE_OF_NOISE][xLow%SIZE_OF_NOISE];
		highB = noise[zLow% SIZE_OF_NOISE][yLevel%SIZE_OF_NOISE][(xLow+1)%SIZE_OF_NOISE];
		
		lowT = noise[(zLow+1)%SIZE_OF_NOISE][yLevel%SIZE_OF_NOISE][xLow%SIZE_OF_NOISE];
		highT = noise[(zLow+1)% SIZE_OF_NOISE][yLevel%SIZE_OF_NOISE][(xLow + 1) % SIZE_OF_NOISE];

		return Linear(Linear(lowB, highB, xt), Linear(lowT, highT, xt), zt);
	}
};



#endif
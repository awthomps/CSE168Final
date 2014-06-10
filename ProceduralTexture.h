#ifndef CSE168_PROCEDURALTEXTURE_H
#define CSE168_PROCEDURALTEXTURE_H

#include "Material.h";
#include <random>;

#define SIZE_OF_NOISE 50;

class ProceduralTexture : public Material {
public:
	ProceduralTexture() {
		//generate noise:
		for (unsigned int i = 0; i < SIZE_OF_NOISE; ++i) {
			for (unsigned int j = 0; j < SIZE_OF_NOISE; ++j) {
				for (unsigned int k = 0; k < SIZE_OF_NOISE; ++k) {
					noise[i][j][k] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
			}
		}
	}
	~ProceduralTexture();
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) = 0;
	virtual void GenerateSample(Color &color, Vector3 &sample, const Vector3 &in, const Intersection &hit) = 0;

protected:
	float noise[SIZE_OF_NOISE][SIZE_OF_NOISE][SIZE_OF_NOISE];
};



#endif
#ifndef CSE168_WOOD_H
#define CSE168_WOOD_H

#include "ProceduralTexture.h"

class Wood : public ProceduralTexture {
public:
	Wood() {
		scale = 1.0f;
		orientation = ORIENTATION_X;
		unsigned int size = 2;
		Color colors[2];
		colors[0] = Color(Vector3(139.0 / 255.0, 69.0 / 255.0, 29.0 / 255.0) / 2.0f);
		colors[1] = Color(222.0 / 255.0, 184.0 / 255.0, 135.0 / 255.0);
		SetColorMap(size, colors);
	}


	Color GenerateColor(Vector3 v) {
		v = v / scale;
		float val = SampleFunction(v.x, v.y, v.z);
		noiseDistance = 10.0f;
		float sampleVal = val - floor(val); //get a value from 0-1.0
		if( sampleVal < 0.0 || sampleVal > 1.0) std::cout << sampleVal << std::endl;
		return ColorFromMap(sampleVal);
	}

	void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
		col.Multiply(Color(GenerateColor(hit.Position).getInVector3() * 1.0f / PI));
	}

	void GenerateSample(Color &color, Vector3 &sample, const Vector3 &in, const Intersection &hit) {
		float s, t, u, v;
		Vector3 preTrans;
		s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		u = 2.0f * PI * s;
		t = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v = sqrt(1.0 - t);

		preTrans.x = v * cos(u);
		preTrans.y = sqrt(t);
		preTrans.z = v * sin(u);

		//orient the h vector into the surface coordinate space:
		Matrix34 coordinateSpace;
		coordinateSpace.a = hit.TangentU;
		coordinateSpace.b = hit.Normal;
		coordinateSpace.c = hit.TangentV;
		coordinateSpace.d = Vector3(0.0f, 0.0f, 0.0f);
		coordinateSpace.Transform3x3(preTrans, sample);
		//color = DiffuseColor;
		Vector3 inCrossN = in;
		inCrossN.Cross(in, hit.Normal);
		color = GenerateColor(hit.Position);
	}

private:
	float SampleFunction(float s, float t, float r) {
		if (orientation == ORIENTATION_X) {
			return ((t - origin.y)*(t - origin.y)) + ((r - origin.z)*(r - origin.z));
		}
		else if (orientation == ORIENTATION_Y) {
			return ((s - origin.x)*(s - origin.x)) + ((r - origin.z)*(r - origin.z));
		}
		else {
			return ((s - origin.x)*(s - origin.x)) + ((t - origin.y)*(t - origin.y));
		}
	}


};






#endif
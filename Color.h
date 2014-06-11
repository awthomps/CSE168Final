////////////////////////////////////////
// Color.h
////////////////////////////////////////

#ifndef CSE168_COLOR_H
#define CSE168_COLOR_H

#include "Core.h"
#include "Vector3.h"

////////////////////////////////////////////////////////////////////////////////

class Color {
public:
	Color()									{Red=Green=Blue=1.0;}
	Color(float r, float g, float b)			{ Red = r; Green = g; Blue = b; rgb2hsv(); }
	Color(Vector3 c)						{ Red = c.x; Green = c.y, Blue = c.z;  rgb2hsv(); }

	void Set(float r, float g, float b)		{ Red = r; Green = g; Blue = b; rgb2hsv(); }

	void Add(const Color c)					{ Red += c.Red; Green += c.Green; Blue += c.Blue; rgb2hsv(); }
	void AddScaled(const Color c, float s)	{ Red += s*c.Red; Green += s*c.Green; Blue += s*c.Blue; rgb2hsv(); }
	void Scale(float s)						{ Red *= s; Green *= s; Blue *= s; rgb2hsv(); }
	void Scale(const Color c, float s)		{ Red = s*c.Red; Green = s*c.Green; Blue = s*c.Blue; rgb2hsv(); }
	void Multiply(const Color c)			{ Red *= c.Red; Green *= c.Green; Blue *= c.Blue; rgb2hsv(); }
	Vector3 getInVector3()					{ return Vector3(Red, Green, Blue); }

	bool equals(Color c) { return (Red == c.Red && Green == c.Green && Blue == c.Blue); }

	int ToInt() {
		int r=(Red<0) ? 0 : ((Red>=1.0) ? 255 : int(Red*256.0f));
		int g=(Green<0) ? 0 : ((Green>=1.0) ? 255 : int(Green*256.0f));
		int b=(Blue<0) ? 0 : ((Blue>=1.0) ? 255 : int(Blue*256.0f));
		return (r<<16) | (g<<8) | b;
	}
	void FromInt(int c)						{Set(float((c>>16)&0xff)/255.0f,float((c>>8)&0xff)/255.0f,float(c&0xff)/255.0f);}
	void FromLinearInterpolation(Color a, Color b, float t) {
		h = Linear(a.h, b.h, t);
		s = Linear(a.s, b.s, t);
		v = Linear(a.v, b.v, t);
		hsv2rgb(); //get rgb colors
	}

	static Color WHITE,GREY,BLACK;
	static Color RED,YELLOW,BLUE,GREEN;

private:
	float Red,Green,Blue;
	float h, s, v;

	void rgb2hsv() {
		double min, max, delta;
		min = Min(Red, Green, Blue);
		max = v = Max(Red, Green, Blue);

        delta = max - min;
		if (max > 0.0) {
			s = (delta / max);
		}
		else {
			// r = g = b = 0                        // s = 0, v is undefined
			s = 0.0;
			h = NAN;                            // its now undefined
			return;
		}
		if (Red >= max)                           // > is bogus, just keeps compilor happy
			h = (Green - Blue) / delta;        // between yellow & magenta
		else
		if (Green >= max)
			h = 2.0 + (Blue - Red) / delta;  // between cyan & yellow
		else
			h = 4.0 + (Red - Green) / delta;  // between magenta & cyan

		h *= 60.0;                              // degrees

		if (h < 0.0) h += 360.0;
	}

	void hsv2rgb() {
		//http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
		double hh, p, q, t, ff;
		long i;

		if (s <= 0.0) {
			Red = v;
			Green = v;
			Blue = v;
			return;
		}
		hh = h;
		if (hh >= 360.0) hh = 0.0;
		hh /= 60.0;
		i = (long)hh;
		ff = hh - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * ff));
		t = v * (1.0 - (s * (1.0 - ff)));

		switch (i) {
		case 0:
			Red = v;
			Green = t;
			Blue = p;
			break;
		case 1:
			Red = q;
			Green = v;
			Blue = p;
			break;
		case 2:
			Red = p;
			Green = v;
			Blue = t;
			break;
		case 3:
			Red = p;
			Green = q;
			Blue = v;
			break;
		case 4:
			Red = t;
			Green = p;
			Blue = v;
			break;
		case 5:
		default:
			Red = v;
			Green = p;
			Blue = q;
			break;
		}
		return;
	}

};

////////////////////////////////////////////////////////////////////////////////

#endif

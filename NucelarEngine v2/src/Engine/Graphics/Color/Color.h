#pragma once
#include "vec4.hpp"
class Color {
public:
	union {
		struct {
			float r, g, b, a;
		};

		float v[4];
	};
	//Default constructor
	Color():r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

	Color(float _r, float _g, float _b, float _a) {
		if (_r >= 0.0f && _r <= 1.0f)
			r = _r;
		else
			r = _r / 255.0f;

		if (_g >= 0.0f && _g <= 1.0f)
			g = _g;
		else
			g = _g / 255.0f;

		if (_b >= 0.0f && _b <= 1.0f)
			b = _b;
		else
			b = _b / 255.0f;

		if (_a >= 0.0f && _a <= 1.0f)
			a = _a;
		else
			a = _a / 255.0f;
	}


	//Copy constructor
	Color(const Color& c):r(c.r), g(c.g), b(c.b), a(c.a) {}

	Color(const glm::vec4 vec) {
		r = vec.x;
		g = vec.y;
		b = vec.z;
		a = vec.w;
	}
	Color(unsigned c) {
		unsigned rr, gg, bb, aa;
		// decompose

		
		rr = c & 255;
		gg = c & (255 << 8);
		bb = c & (255 << 16);
		aa = c & (255 << 24);
		// float
		r = (float)rr / 255.0f;
		g = (float)gg / 255.0f;
		b = (float)bb / 255.0f;
		a = (float)aa / 255.0f;
	}

	Color operator = (const Color& rhs);
	Color operator * (const Color& rhs);
	Color operator *= (const Color& rhs);
	Color operator * (const float& rhs);
	Color operator *= (const float& rhs);
	Color operator + (const Color& rhs);
	Color operator += (const Color& rhs);
	Color operator - (const Color& rhs);
	Color operator -= (const Color& rhs);
	Color operator !();
};
#pragma once
#include "vec4.hpp"
class Color {
public:
	float r, g, b, a;
	//Default constructor
	Color():r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

	Color(float _r, float _g, float _b, float _a) {
		if (_r > 0 && _r < 1)
			r = _r;
		else
			r = _r / 255.0f;

		if (_g > 0 && _g < 1)
			g = _g;
		else
			g = _g / 255.0f;

		if (_b > 0 && _b < 1)
			b = _b;
		else
			b = _b / 255.0f;

		if (_a > 0 && _a < 1)
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


};
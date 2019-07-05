#pragma once
#include "Color.h"

class Vertex {
	float x, y, z;
	Color c;

	Vertex(float _x = 0, float _y = 0, float _z = 0, Color _c = Color{}) {
		x = _x;
		y = _y;
		z = _z;
		c = _c;
	}

	Vertex(const Vertex & v) {
		x = v.x;
		y = v.y;
		z = v.z;
		c = v.c;
	}

	Vertex operator+ (const Vertex& rhs);
	Vertex operator+= (const Vertex& rhs);
	Vertex operator- (const Vertex& rhs);
	Vertex operator-= (const Vertex& rhs);

};
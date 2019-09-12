#pragma once
#include "Color/Color.h"
#include "vec3.hpp"

class Vertex {
	glm::vec3 mPosition;
	Color c;

	Vertex(float _x = 0, float _y = 0, float _z = 0, Color _c = Color{}) {
		mPosition.x = _x;
		mPosition.y = _y;
		mPosition.z = _z;
		c = _c;
	}

	Vertex(const Vertex & v) {
		mPosition.x = v.mPosition.x;
		mPosition.y = v.mPosition.y;
		mPosition.z = v.mPosition.z;
		c = v.c;
	}

	Vertex operator+ (const Vertex& rhs);
	Vertex operator+= (const Vertex& rhs);
	Vertex operator- (const Vertex& rhs);
	Vertex operator-= (const Vertex& rhs);
	Vertex operator* (const float& rhs);
	Vertex operator*= (const float& rhs);

};
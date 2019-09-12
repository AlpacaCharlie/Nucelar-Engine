#include "Vertex.h"

Vertex Vertex::operator+ (const Vertex& rhs) {
	return Vertex{ mPosition.x + rhs.mPosition.x,
		mPosition.y + rhs.mPosition.y,
		mPosition.z + rhs.mPosition.z,
		c};
}
Vertex Vertex::operator+= (const Vertex& rhs) {
	mPosition.x += rhs.mPosition.x;
	mPosition.y += rhs.mPosition.y;
	mPosition.z += rhs.mPosition.z;
	c;

	return *this;
}
Vertex Vertex::operator- (const Vertex& rhs) {
	return Vertex{ mPosition.x + rhs.mPosition.x,
		mPosition.y + rhs.mPosition.y,
		mPosition.z + rhs.mPosition.z,
		c };
}
Vertex Vertex::operator-= (const Vertex& rhs) {
	mPosition.x -= rhs.mPosition.x;
	mPosition.y -= rhs.mPosition.y;
	mPosition.z -= rhs.mPosition.z;

	return *this;
}
Vertex Vertex::operator* (const float& rhs) {
	return Vertex{ mPosition.x *= rhs,
		mPosition.y *= rhs,
		mPosition.z *= rhs,
		c };
}
Vertex Vertex::operator*= (const float& rhs) {
	mPosition.x -= rhs;
	mPosition.y -= rhs;
	mPosition.z -= rhs;

	return *this;
}

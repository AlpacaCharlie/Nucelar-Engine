#include "Color.h"

Color Color::operator = (const Color& rhs) {
	return Color{ rhs };
}
Color Color::operator * (const Color& rhs) {
	return Color{ r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a };
}
Color Color::operator *= (const Color& rhs) {
	return *this = Color{ r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a };
}
Color Color::operator * (const float& rhs) {
	return Color{ r * rhs, g * rhs, b * rhs, a * rhs }; 
}
Color Color::operator *= (const float& rhs) {
	return *this = Color{ r * rhs, g * rhs, b * rhs, a * rhs };
}
Color Color::operator + (const Color& rhs) {
	return Color{ r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
}
Color Color::operator += (const Color& rhs) {
	return *this = Color{ r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
}
Color Color::operator - (const Color& rhs) {
	return Color{ r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
}
Color Color::operator -= (const Color& rhs) {
	return *this = Color{ r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
}
Color Color::operator !() {
	return Color{ 1.0f - r, 1.0f - g, 1.0f - b, 1.0f - a };
}

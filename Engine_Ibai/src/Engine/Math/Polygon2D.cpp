#include "MyMath.h"

/*! @PROVIDED
*	\brief	Draws the polygon with the provided color and transform.
*/
void Polygon2D::Draw(u32 color, Matrix33 * vtx_transform) const
{
	// can't draw polygon if we don't have at least
	// 2 vertices
	if (mVertices.size() <= 1)
		return;

	// set transform if necessary transform 
	if (vtx_transform != NULL) {
		AEMtx33 mat = *vtx_transform;
		AEGfxSetTransform(&mat);
	}

	// Draw line between each vertices
	for (u32 i = 0; i < mVertices.size() - 1; ++i)
	{
		auto & v1 = mVertices[i];
		auto & v2 = mVertices[i + 1];
		AEGfxLine(v1.x, v1.y, 0, color, v2.x, v2.y, 0, color);
	}
	// Draw last line from last to first vertex
	auto & v1 = mVertices[0];
	auto & v2 = mVertices[mVertices.size() - 1];
	AEGfxLine(v1.x, v1.y, 0, color, v2.x, v2.y, 0, color);

	// force draw on graphics system
	AEGfxFlush();
}


// ------------------------------------------------------------------------
// STATIC INTERFACE
// ------------------------------------------------------------------------
/*! @PROVIDED
*	\brief	Creates a quad polygon.
*/
Polygon2D Polygon2D::MakeQuad()
{
	// result polygon
	Polygon2D res(4);

	// create vertices
	res[0] = { -0.5f, 0.5f };
	res[1] = { -0.5f, -0.5f };
	res[2] = { 0.5f, -0.5f };
	res[3] = { 0.5f, 0.5f };

	return res;
}

/*! @PROVIDED
*	\brief	Creates a 5-sided polygon.
*/
Polygon2D Polygon2D::MakePentagon()
{
	return MakeStandardPoly(5);
}

/*! @PROVIDED
*	\brief	Creates a 6-sided polygon.
*/
Polygon2D Polygon2D::MakeHexagon()
{
	return MakeStandardPoly(6);
}

/*! @PROVIDED
*	\brief	Creates a 7-sided polygon.
*/
Polygon2D Polygon2D::MakeSeptagon()
{
	return MakeStandardPoly(7);
}

/*! @PROVIDED
*	\brief	Creates a 8-sided polygon.
*/
Polygon2D Polygon2D::MakeOctagon()
{
	return MakeStandardPoly(8);
}

/*! @PROVIDED
*	\brief	Creates a n-sided polygon.
*/
Polygon2D Polygon2D::MakeStandardPoly(u32 side)
{
	Polygon2D res(side);
	res[0] = { 0.5f, 0.0f };
	f32 alpha = (2.0f*PI) / (f32)side;
	for (u32 i = 1; i < side; ++i) {

		// set current point to previous
		// before rotation
		res[i] = res[i - 1];
		
		// compute rotation vars
		f32 tmp = res[i].x;
		f32 cA = cosf(alpha);
		f32 sA = sinf(alpha);

		// apply rotation to get new point
		res[i].x = cA * res[i].x - sA * res[i].y;
		res[i].y = sA * tmp + cA * res[i].y;
	}
	return res;
}

Polygon2D::Polygon2D()
{
}

Polygon2D::Polygon2D(u32 size)
{
}

void Polygon2D::AddVertex(const Vector2 & vtx)
{
}

Vector2 & Polygon2D::operator[](u32 idx)
{
	// TODO: insert return statement here
	return Vector2();
}

void Polygon2D::Clear()
{
}

u32 Polygon2D::GetSize() const
{
	return u32();
}

void Polygon2D::SetSize(u32 size)
{
}

std::vector<Vector2> Polygon2D::GetTransformedVertices(const Matrix33 & mat_transform) const
{
	return std::vector<Vector2>();
}

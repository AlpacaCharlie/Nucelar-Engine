// ----------------------------------------------------------------------------
// Project Name		:	Project 2
// File Name		:	Engine.h
// Author			:	Thomas Komair
// Creation Date	:	February 21st, 2013
// Purpose			:	Defines the engine headers.
// History			:
// - 2013/2/21		:	Initial Implementation.
// ----------------------------------------------------------------------------
#ifndef ENGINE_H_
#define ENGINE_H_

#include "GSM\GameStateManager.h"
#include "Math\MyMath.h"
#include "Physics\RigidBody.h"
#include "Physics\CollisionSystem.h"

// conversion to and from ae matrix
#include "AEMath.h"
inline AEMtx33 to_ae_mtx(const Matrix33& mtx)
{
	AEMtx33 ae_mtx;
	std::memcpy(ae_mtx.v, mtx.v, sizeof(f32) * 9);
	return ae_mtx;
}
inline AEVec2 to_ae_vec2(const Vector2 &vec)
{
	AEVec2 ae_vec2 = { vec.x, vec.y };
	return ae_vec2;
}
inline Vector2 from_ae_vec2(const AEVec2 &ae_vec)
{
	Vector2 vec = { ae_vec.x, ae_vec.y };
	return vec;
}
inline Matrix33 from_ae_mtx(const AEMtx33 &ae_mtx)
{
	Matrix33 mtx;
	std::memcpy(mtx.v, ae_mtx.v, sizeof(f32) * 9);
	return mtx;
}

#endif
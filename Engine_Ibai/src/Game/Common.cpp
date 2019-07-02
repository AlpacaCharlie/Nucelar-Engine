#include <AEEngine.h>
#include <GAM150.h>
#include "..\Engine\Engine.h"
#include "Common.h"
#include <cstdlib>

// ----------------------------------------------------------------------------
#pragma region// ASSIGNMENT 2
void MakeQuad(Model * model)
{
	if (model->mVertexArray)
		free(model->mVertexArray);

	model->mVertexCount = 8;
	model->mVertexArray = (Vector2*)malloc(sizeof(Vector2)* model->mVertexCount);

	// temp
	f32 h = 0.5f;

	// left side
	model->mVertexArray[0] = { -h, h };
	model->mVertexArray[1] = { -h, -h };

	// bottom side
	model->mVertexArray[2] = { -h, -h };
	model->mVertexArray[3] = { h, -h };

	// right side
	model->mVertexArray[4] = { h, -h };
	model->mVertexArray[5] = { h, h };

	// top side
	model->mVertexArray[6] = { -h, h };
	model->mVertexArray[7] = { h, h };
}
void MakeCircle(Model * model)
{
	if (model->mVertexArray)
		free(model->mVertexArray);

	// allocate memory for the vertices
	const u32 precision = 20;
	model->mVertexCount = precision * 2;
	model->mVertexArray = (Vector2*)malloc(sizeof(Vector2)* model->mVertexCount);


	// generate circle model
	float angle = 0.0f;
	float angle_offset = TWO_PI / (float)precision;
	float hrad = .5f;
	int i = 0;
	while (angle < TWO_PI)
	{
		float p0x = AECos(angle) * hrad; float p0y = AESin(angle) * hrad;
		angle += angle_offset;
		float p1x = AECos(angle) * hrad; float p1y = AESin(angle) * hrad;

		model->mVertexArray[i].x = p0x;	
		model->mVertexArray[i++].y = p0y;
		model->mVertexArray[i].x = p1x;
		model->mVertexArray[i++].y = p1y;

	}
}

void CopyModel(Model * srcModel, Model * dstModel)
{
	// free any previously allocated array
	if (dstModel->mVertexArray)
		free(dstModel->mVertexArray);

	// store the vertex count
	dstModel->mVertexCount = srcModel->mVertexCount;

	// allocate new vertex array into destination
	dstModel->mVertexArray = (Vector2*)malloc(sizeof(Vector2)* dstModel->mVertexCount);

	// copy the memory in one shot
	memcpy(dstModel->mVertexArray, srcModel->mVertexArray, sizeof(Vector2)* srcModel->mVertexCount);
}
void DrawModel(Model *  model, unsigned color)
{
	AEGfxSetTransform(&AEMtx33::Identity());
	for (u32 i = 0; i < model->mVertexCount; ++i)
	{
		// use pointers to reference the vector
		Vector2 * p0, *p1;

		if (i == model->mVertexCount - 1)
		{
			p0 = model->mVertexArray + i; // last vertex
			p1 = model->mVertexArray;		// first vertex
		}
		else
		{
			p0 = model->mVertexArray + i;		// current vertex
			p1 = model->mVertexArray + i + 1; // next vertex
		}
		AEGfxLine(p0->x, p0->y, 0.0f, color, p1->x, p1->y, 0.0f, color);
	}
	AEGfxFlush();
}
void TransformModel(Model * inModel, Model * outModel, const Transform2D & transform)
{
	for (u32 i = 0; i < inModel->mVertexCount; ++i)
	{
		outModel->mVertexArray[i] = transform * inModel->mVertexArray[i];
	}
}

#pragma endregion
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#pragma region// ASSIGNMENT 3

RigidBody* CreateRandBoxWithMass(f32 mass, Vector2 gravity)
{
	RigidBody * phxObj = (RigidBody*)gObjMgr.AddObject(new RigidBody(), "Box",
		AERandFloat(-300, 300), -AERandFloat(0, 200),
		AERandFloat(20, 50), AERandFloat(20, 50),
		0.0f);
	phxObj->mColor = 0xFFFFFFFF;
	phxObj->mInvMass = FLOAT_ZERO(mass) ? 0.0f : 1.0f / mass;
	phxObj->mGravity = gravity;
	phxObj->mCollisionShape = CSHAPE_OBB;

	// add to the collision system
	gCollisionSystem.AddRigidBody(phxObj, !FLOAT_ZERO(mass));

	return phxObj;
}
RigidBody* CreateRandCircleWithMass(f32 mass, Vector2 gravity)
{
	f32 radius = AERandFloat(20, 60);
	RigidBody * phxObj = (RigidBody*)gObjMgr.AddObject(new RigidBody(), "Circle",
		AERandFloat(-300, 300), -AERandFloat(0, 200),
		radius,radius,
		0.0f);

	phxObj->mCollisionShape = CSHAPE_CIRCLE;
	phxObj->mColor = 0xFFFFFFFF;
	phxObj->mInvMass = FLOAT_ZERO(mass) ? 0.0f : 1.0f / mass;
	phxObj->mGravity = gravity;

	gCollisionSystem.AddRigidBody(phxObj, !FLOAT_ZERO(mass));

	return phxObj;
}


#pragma endregion
// ----------------------------------------------------------------------------

#include "Sandbox.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "Level_4.h"
void GameFlow()
{
	// Quit/Restart
	if (AEInputKeyTriggered('R'))
		gAEGameStateNext = AE_GS_RESTART;
	if (AEInputKeyTriggered(VK_ESCAPE))
		gAEGameStateNext = AE_GS_QUIT;

	// Changing the states
	if (AEInputKeyTriggered('1'))
		gAEGameStateNext = GS_LEVEL_1;
	if (AEInputKeyTriggered('2'))
		gAEGameStateNext = GS_LEVEL_2;
	if (AEInputKeyTriggered('3'))
		gAEGameStateNext = GS_LEVEL_3;
	if (AEInputKeyTriggered('4'))
		gAEGameStateNext = GS_LEVEL_4;
	if (AEInputKeyTriggered('5'))
		gAEGameStateNext = GS_LEVEL_SANDBOX;
}
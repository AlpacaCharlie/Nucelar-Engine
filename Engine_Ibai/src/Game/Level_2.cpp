// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	Level.cpp
// Author			:	Thomas Komair
// Creation Date	:	2013/04/26
// Purpose			:	Implementation of demo level game states functions.
// History			:
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// INCLUDES
#include <AEEngine.h>
#include <GAM150.h>
#include "..\Engine\Engine.h"
#include "Common.h"
#include "Level_2.h"
// ---------------------------------------------------------------------------
// GLOBAL VARIABLES AND DEFINITIONS

// level 2
namespace Level_2
{
	RigidBody *gObjects[2],  *gControlled;// = &gObjects[0];
	enum EColors { gRed = 0xFFFFCC22, gBlue = 0xFFCC33FF };
	bool gCollided = false;
	Contact gContact;

	// Player Input-> Mouse controls.
	void PlayerInput();
}
using namespace Level_2;
// ---------------------------------------------------------------------------
// HELPER FUNCTIONS DECLARATIONS


// ---------------------------------------------------------------------------
// GAME STATE FUNCTIONS
void Level_2_Load()
{
}
void Level_2_Init()
{
	gObjects[0] = CreateRandBoxWithMass(1.0f, Vector2(0,0));
	gObjects[0]->mCollisionShape = CSHAPE_AABB;
	gObjects[1] = CreateRandCircleWithMass(1.0f, Vector2(0, 0));
	gControlled = gObjects[0];

	// Set the background color to black
	AEGfxSetClearColor(0xFF000000);
	
	gObjects[0]->mPosition = Vector2(-10, 0);
	gObjects[0]->mScale = Vector2(200, 200);

	gObjects[1]->mPosition = Vector2(100, 0);
	gObjects[1]->mScale = Vector2(25, 25);
}
void Level_2_Update()
{
	GameFlow();
	gObjMgr.Update();
	PlayerInput();

	// TEst for intersection
	RigidBody * rect = gObjects[0];
	RigidBody * circle = gObjects[1];
	gCollided = rect->mCollisionShape == CSHAPE_AABB
		? StaticRectToStaticCircleEx(&Vector2(rect->mPosition), rect->mScale.x, rect->mScale.y, &Vector2(circle->mPosition), circle->mScale.x, &gContact)
		: StaticOBBToStaticCircleEx(&Transform2D(rect->mPosition, rect->mScale, rect->mRotation), &Vector2(circle->mPosition), circle->mScale.x, &gContact);
	if (gCollided && AEInputKeyPressed(32))
		gCollisionSystem.ResolveContactPenetration(rect, circle, &gContact);
}
void Level_2_Render()
{
	if (gObjects[0]->mCollisionShape == CSHAPE_AABB)
		AEGfxPrint(0, 0, 0xFFFFFFFF, "LEVEL 2: AABB vs CIRCLE COLLISION");
	else
		AEGfxPrint(0, 0, 0xFFFFFFFF, "LEVEL 2: OBB vs CIRCLE COLLISION");

	gObjects[0]->mColor = gRed;
	gObjects[1]->mColor = gBlue;
	gObjMgr.Render();

	AEGfxReset();
	AEGfxLine(0, 5, 0, 0xFFFFFF00, 0, -5, 0, 0xFFFFFF00);
	AEGfxLine(5, 0, 0, 0xFFFFFF00, -5, 0, 0, 0xFFFFFF00);
	AEGfxFlush();

	{
		auto pos = Vector2(gObjects[0]->mPosition.x + gAESysWinWidth / 2.0f, -gObjects[0]->mPosition.y + gAESysWinHeight / 2.0f);
		AEGfxPrint((u32)pos.x,(u32) pos.y, gObjects[0]->mColor, "AABB");
	}
	{
		auto pos = Vector2(gObjects[1]->mPosition.x + gAESysWinWidth / 2.0f, -gObjects[1]->mPosition.y + gAESysWinHeight / 2.0f);
		AEGfxPrint((u32)pos.x, (u32)pos.y, gObjects[1]->mColor, "CIRCLE");
	}
	// Draw the contact
	if (gCollided)
	{

		// render the point of intersection
		AEGfxRect(gContact.mPi.x, gContact.mPi.y, 0, 5, 5, 0xFFFF00FF);

		// draw the normal from the point of interesection
		Vector2 endNormal = gContact.mPi + gContact.mNormal * gContact.mPenetration;
		AEGfxLine(gContact.mPi.x, gContact.mPi.y, 0.0f, 0xFFFFFF00, endNormal.x, endNormal.y, 0.0f, 0xFFFFFF00);
	}
	AEGfxFlush();
}
void Level_2_Free()
{
	gObjMgr.FreeAllObjects();
	gCollisionSystem.ClearBodies();
}
void Level_2_Unload()
{
}

// ---------------------------------------------------------------------------
// HELPER FUNCTIONS IMPLEMENTATIONS

namespace Level_2
{
	void PlayerInput()
	{
		f32 speed = 1.0f;
		f32 scaleSpeed = 1.0f;
		f32 rotSpeed = AEDegToRad(1.0f);

		if (AEInputKeyTriggered('C'))
		{
			gControlled = gControlled == gObjects[0] ? gObjects[1] : gObjects[0];
		}

		if (AEInputKeyPressed('A'))
			gControlled->mPosition.x -= speed;
		if (AEInputKeyPressed('D'))
			gControlled->mPosition.x += speed;
		if (AEInputKeyPressed('S'))
			gControlled->mPosition.y -= speed;
		if (AEInputKeyPressed('W'))
			gControlled->mPosition.y += speed;

		// scale
		if (AEInputKeyPressed('J'))
			gControlled->mScale.x -= scaleSpeed;
		if (AEInputKeyPressed('L'))
			gControlled->mScale.x += scaleSpeed;
		if (AEInputKeyPressed('K'))
			gControlled->mScale.y -= scaleSpeed;
		if (AEInputKeyPressed('I'))
			gControlled->mScale.y += scaleSpeed;

		// rotation
		if (AEInputKeyPressed('Q') && gControlled == gObjects[0]){
			gControlled->mRotation += rotSpeed;
			gObjects[0]->mCollisionShape = CSHAPE_OBB;
		}
		if (AEInputKeyPressed('E') && gControlled == gObjects[0]){
			gControlled->mRotation -= rotSpeed;
			gObjects[0]->mCollisionShape = CSHAPE_OBB;
		}

		if (AEInputMousePressed(AE_MOUSE_LEFT))
		{
			gObjects[0]->mPosition = gAEMousePosition;
		}
		if (AEInputMousePressed(AE_MOUSE_RIGHT))
		{
			gObjects[1]->mPosition = gAEMousePosition;
		}
	}
}
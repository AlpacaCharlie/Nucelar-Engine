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
#include "Level_3.h"
// ---------------------------------------------------------------------------
// GLOBAL VARIABLES AND DEFINITIONS

// level 2
namespace Level_3
{
	RigidBody *gOBB1, *gOBB2, *gControlled;// = &gOBB1;
	u32 gOBB1Color = 0xFFFFCC22;
	u32 gOBB2Color = 0xFFCC33FF;
	bool gRotated = false;
	bool gCollided = false;
	Contact gContact;
}
using namespace Level_3;
// ---------------------------------------------------------------------------
// HELPER FUNCTIONS DECLARATIONS

// Move Controlled OBB
void MoveOBB();

// ---------------------------------------------------------------------------
// GAME STATE FUNCTIONS
void Level_3_Load()
{
}
void Level_3_Init()
{
	gOBB1 = CreateRandBoxWithMass(1.0f, Vector2(0,0));
	gOBB2 = CreateRandBoxWithMass(1.0f, Vector2(0, 0));
	gControlled = gOBB1;

	// Set the background color to black.
	AEGfxSetClearColor(0xFF000000);
	
	gOBB1->mPosition = Vector2(-10, 0);
	gOBB1->mScale = Vector2(200, 160);
	gOBB1->mRotation= 0.0f;

	gOBB2->mPosition = Vector2(100, 0);
	gOBB2->mScale = Vector2(100, 100);
	gOBB2->mRotation = 0.0f;

	// no box is rotated
	gRotated = false;
}
void Level_3_Update()
{
	GameFlow();

	gObjMgr.Update();

	// Move Controller OBB
	MoveOBB();

	// TEst for intersection
	if (gRotated)
	{
		Transform2D obb1 = { gOBB1->mPosition, gOBB1->mScale, gOBB1->mRotation };
		Transform2D obb2 = { gOBB2->mPosition, gOBB2->mScale, gOBB2->mRotation };
		gCollided = OrientedRectToOrientedRectEx(&obb1, &obb2, &gContact);
	}
	else
	{
		Vector2 p1 = gOBB1->mPosition, s1 = gOBB1->mScale,
				p2 = gOBB2->mPosition, s2 = gOBB2->mScale;
		gCollided = StaticRectToStaticRectEx(&p1, &s1, &p2, &s2, &gContact);
	}

	if (gCollided && AEInputKeyPressed(32))
		gCollisionSystem.ResolveContactPenetration(gOBB1, gOBB2, &gContact);
}
void Level_3_Render()
{
	if (gRotated)
		AEGfxPrint(0, 0, 0xFFFFFFFF, "LEVEL 3: OBB COLLISION");
	else
		AEGfxPrint(0, 0, 0xFFFFFFFF, "LEVEL 3: AABB COLLISION");

	gOBB1->mColor = gOBB1Color;
	gOBB2->mColor = gOBB2Color;
	gObjMgr.Render();

	AEGfxReset();
	AEGfxLine(0, 5, 0, 0xFFFFFF00, 0, -5, 0, 0xFFFFFF00);
	AEGfxLine(5, 0, 0, 0xFFFFFF00, -5, 0, 0, 0xFFFFFF00);
	AEGfxFlush();

	{
		auto pos = Vector2(gOBB1->mPosition.x + gAESysWinWidth / 2.0f, -gOBB1->mPosition.y + gAESysWinHeight / 2.0f);
		if (gRotated)
			AEGfxPrint((u32)pos.x, (u32)pos.y, gOBB1Color, "OBB-1");
		else
			AEGfxPrint((u32)pos.x, (u32)pos.y, gOBB1Color, "AABB-1");
	}
	{
		auto pos = Vector2(gOBB2->mPosition.x + gAESysWinWidth / 2.0f, -gOBB2->mPosition.y + gAESysWinHeight / 2.0f);
		if (gRotated)
			AEGfxPrint((u32)pos.x, (u32)pos.y, gOBB2Color, "OBB-2");
		else
			AEGfxPrint((u32)pos.x, (u32)pos.y, gOBB1Color, "AABB-2");
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
void Level_3_Free()
{
	gObjMgr.FreeAllObjects();
	gCollisionSystem.ClearBodies();
}
void Level_3_Unload()
{
}

// ---------------------------------------------------------------------------
// HELPER FUNCTIONS IMPLEMENTATIONS

void MoveOBB()
{
	f32 speed = 1.0f;
	f32 scaleSpeed = 1.0f;
	f32 rotSpeed = AEDegToRad(1.0f);

	if (AEInputKeyTriggered('C'))
	{
		gControlled = gControlled == gOBB1 ? gOBB2 :gOBB1;
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

	// rotation -> note change to obb test once 
	// at least one box is rotated. 
	if (AEInputKeyPressed('Q')){
		gControlled->mRotation += rotSpeed;
		gOBB1->mCollisionShape = CSHAPE_OBB;
		gOBB2->mCollisionShape = CSHAPE_OBB;
		gRotated = true;
	}
	if (AEInputKeyPressed('E')){
		gControlled->mRotation -= rotSpeed;
		gOBB1->mCollisionShape = CSHAPE_OBB;
		gOBB2->mCollisionShape = CSHAPE_OBB;
		gRotated = true;
	}
	if (AEInputMousePressed(AE_MOUSE_LEFT))
	{
		gOBB1->mPosition = gAEMousePosition;
	}
	if (AEInputMousePressed(AE_MOUSE_RIGHT))
	{
		gOBB2->mPosition = gAEMousePosition;
	}
}
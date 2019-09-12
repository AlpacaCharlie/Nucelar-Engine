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
#include "Level_4.h"

// ---------------------------------------------------------------------------
// GLOBAL VARIABLES AND DEFINITIONS

// level 4
namespace Level_4
{
	RigidBody *gPolyBody1, *gPolyBody2, *gControlled;
	Polygon2D gPoly1, gPoly2;
	u32 gPoly1Color = 0xFFFFCC22;
	u32 gPoly2Color = 0xFFCC33FF;
	bool gCollided = false;
	Contact gContact;
}
using namespace Level_4;
// ---------------------------------------------------------------------------
// HELPER FUNCTIONS DECLARATIONS

// Move Controlled OBB
void MovePoly();

// ---------------------------------------------------------------------------
// GAME STATE FUNCTIONS
void Level_4_Load()
{
}
void Level_4_Init()
{
	// Create the polygon as boxes with no gravity
	gPolyBody1 = CreateRandBoxWithMass(1.0f, Vector2(0,0));
	gPolyBody2 = CreateRandBoxWithMass(1.0f, Vector2(0, 0));

	// by default, we always control the first object
	gControlled = gPolyBody1;

	// Set the background color to black.
	AEGfxSetClearColor(0xFF000000);
	
	// Initialize Polygon 1
	gPoly1 = Polygon2D::MakeStandardPoly(4 + rand() % 10);			// Make polygon shape
	gPolyBody1->mPosition = Vector2(-10, 0);	// Set transform data
	gPolyBody1->mScale = Vector2(200, 160);
	gPolyBody1->mRotation= 0.0f;

	gPoly2 = Polygon2D::MakeStandardPoly(4 + rand() % 10);			// Make polygon shape
	gPolyBody2->mPosition = Vector2(100, 0);	// Set transform data
	gPolyBody2->mScale = Vector2(100, 100);
	gPolyBody2->mRotation = 0.0f;
}
void Level_4_Update()
{
	GameFlow();

	gObjMgr.Update();

	// Move Controller OBB
	MovePoly();

	// TEst for intersection
	Transform2D tr1 = { gPolyBody1->mPosition, gPolyBody1->mScale, gPolyBody1->mRotation };
	Transform2D tr2 = { gPolyBody2->mPosition, gPolyBody2->mScale, gPolyBody2->mRotation };
	gCollided = PolygonToPolygon( &gPoly1, &tr1, &gPoly2, &tr2, &gContact);

	// resolve penetration 
	if (gCollided && AEInputKeyPressed(32))
		gCollisionSystem.ResolveContactPenetration(gPolyBody1, gPolyBody2, &gContact);
}
void Level_4_Render()
{
	AEGfxPrint(0, 0, 0xFFFFFFFF, "LEVEL 4 (EXTRA CREDIT): POLYGON COLLISION");

	// reset colors
	gPolyBody1->mColor = gPoly1Color;
	gPolyBody2->mColor = gPoly2Color;

	// WORLD AXES
	AEGfxReset();
	AEGfxLine(0, 5, 0, 0xFFFFFF00, 0, -5, 0, 0xFFFFFF00);
	AEGfxLine(5, 0, 0, 0xFFFFFF00, -5, 0, 0, 0xFFFFFF00);
	AEGfxFlush();

	// CENTER OF OBJECTS
	{
		auto pos = Vector2(gPolyBody1->mPosition.x + gAESysWinWidth / 2.0f, -gPolyBody1->mPosition.y + gAESysWinHeight / 2.0f);
		AEGfxPrint((u32)pos.x, (u32)pos.y, gPoly1Color, "POLY-1");
	}
	{
		auto pos = Vector2(gPolyBody2->mPosition.x + gAESysWinWidth / 2.0f, -gPolyBody2->mPosition.y + gAESysWinHeight / 2.0f);
		AEGfxPrint((u32)pos.x, (u32)pos.y, gPoly2Color, "POLY-2");
	}

	// DRAW POLYS
	Transform2D tr1 = { gPolyBody1->mPosition, gPolyBody1->mScale, gPolyBody1->mRotation };
	Transform2D tr2 = { gPolyBody2->mPosition, gPolyBody2->mScale, gPolyBody2->mRotation };
	gPoly1.Draw(gPoly1Color, &tr1.GetMatrix());
	gPoly2.Draw(gPoly2Color, &tr2.GetMatrix());

	// reset graphics

	// Draw the contact
	if (gCollided)
	{
		AEGfxReset();
		// render the point of intersection
		AEGfxRect(gContact.mPi.x, gContact.mPi.y, 0, 5, 5, 0xFFFF00FF);

		// draw the normal from the point of interesection
		Vector2 endNormal = gContact.mPi + gContact.mNormal * gContact.mPenetration;
		AEGfxLine(gContact.mPi.x, gContact.mPi.y, 0.0f, 0xFFFFFF00, endNormal.x, endNormal.y, 0.0f, 0xFFFFFF00);

		AEGfxFlush();
	}
}
void Level_4_Free()
{
	gObjMgr.FreeAllObjects();
	gCollisionSystem.ClearBodies();
}
void Level_4_Unload()
{
}

// ---------------------------------------------------------------------------
// HELPER FUNCTIONS IMPLEMENTATIONS

void MovePoly()
{
	f32 speed = 1.0f;
	f32 scaleSpeed = 1.0f;
	f32 rotSpeed = AEDegToRad(1.0f);

	if (AEInputKeyTriggered('C'))
	{
		gControlled = gControlled == gPolyBody1 ? gPolyBody2 :gPolyBody1;
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
	}
	if (AEInputKeyPressed('E')){
		gControlled->mRotation -= rotSpeed;
	}
	if (AEInputMousePressed(AE_MOUSE_LEFT))
	{
		gPolyBody1->mPosition = gAEMousePosition;
	}
	if (AEInputMousePressed(AE_MOUSE_RIGHT))
	{
		gPolyBody2->mPosition = gAEMousePosition;
	}
}
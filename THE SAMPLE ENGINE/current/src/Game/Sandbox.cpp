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
#include "Sandbox.h"

// ---------------------------------------------------------------------------
// GLOBAL VARIABLES AND DEFINITIONS

// Sandbox;
namespace Sandbox
{
	//demo variables
	u32 gInitObjCount = 10;
	Vector2 gGravity = Vector2(0, -250.0f);
	bool gRunPhysics = true;

	//
	//  Editor 
	// 

	// Editor states
	enum EEditorState{ eIdle, eSelect, eTransforming, eCreateCircle, eCreateBox} gEditorState;

	// Editor input handling (mouse and keyboard)
	void EditorInput();

	// Object Selection
	Vector2 gPickStart, gPickEnd;
	OBJECT_PTR_LIST gSelectedObjects;
	OBJECT_PTR_LIST PickObjects(const Vector2 & start);
	OBJECT_PTR_LIST PickObjects(const Vector2 & start, const Vector2 & end);

	// Transform manipulator
	Transform2D gGizmo, gTranformMod;
	f32 gGizmoRadius = 10.0f;
	bool gbGizmoSelected = false;

	// Camera
	Camera gCamera;
	void CamInit();
	void CamUpdate();

	// 
	// Debug 

	// draw aabbs
	bool gDrawAABBs = false;
	void DrawAABBs();
}
using namespace Sandbox;


// ---------------------------------------------------------------------------
// GAME STATE FUNCTIONS
void Sandbox_Load()
{
}
void Sandbox_Init()
{
	// Set the background color to black.
	AEGfxSetClearColor(0xFF000000);
	CamInit();
	gEditorState = eIdle;

	// create the ground
	{
		RigidBody * phxObj = (RigidBody*)gObjMgr.AddObject(new RigidBody(), "Ground",
			0, -250, 1600, 50, 0.0f);
		phxObj->mInvMass = 0.0f;
		phxObj->mColor = 0xFFFFFFFF;
		phxObj->mCollisionShape = CSHAPE_OBB;
		phxObj->mGravity = gGravity;
		gCollisionSystem.AddRigidBody(phxObj, false);

		phxObj = (RigidBody*)gObjMgr.AddObject(new RigidBody(), "Ground",
			-850, 525, 100, 1500, 0.0f);
		phxObj->mInvMass = 0.0f;
		phxObj->mColor = 0xFFFFFFFF;
		phxObj->mCollisionShape = CSHAPE_OBB;
		phxObj->mGravity = gGravity;
		gCollisionSystem.AddRigidBody(phxObj, false);

		phxObj = (RigidBody*)gObjMgr.AddObject(new RigidBody(), "Ground",
			850, 525, 100, 1500, 0.0f);
		phxObj->mInvMass = 0.0f;
		phxObj->mColor = 0xFFFFFFFF;
		phxObj->mCollisionShape = CSHAPE_OBB;
		phxObj->mGravity = gGravity;
		gCollisionSystem.AddRigidBody(phxObj, false);
	}

	// create a couple of boxes that fall on the ground
	for (u32 i = 0; i < gInitObjCount; ++i)
	{
		CreateRandBoxWithMass(1.0f, gGravity);
	}
}
void Sandbox_Update()
{
	GameFlow();
	EditorInput();

	CamUpdate();
	if (gRunPhysics)
		gObjMgr.Update();
	gCollisionSystem.CollideAllBodies();
}
void Sandbox_Draw()
{
	static char buffer[512];
	static char editorState[32];
	switch (gEditorState)
	{
	case eIdle: sprintf_s(editorState, "Idle"); break;
	case eSelect: sprintf_s(editorState, "Selecting"); break;
	case eCreateCircle: sprintf_s(editorState, "Create Circle"); break;
	case eCreateBox: sprintf_s(editorState, "Create Box"); break;
	case eTransforming: sprintf_s(editorState, "Transforming"); break;
	}
	sprintf_s(buffer, "SANDBOX (%s) \n\
					  PHYSICS %s (Press P to toggle)\n\
					  SHOW AABBS: %s (Press L to toggle)\n\
					  DYNAMIC COUNT = %i (+/- to change)\n\
					  STATIC COUNT = %i\n\
					  COLLISION ITERATION = %i (I/O to change)\n\
					  COLLISIONS THIS FRAME = %i\n\
					  FPS = %.3f\n\
					  SPACE [+SHIFT] TO LAUNCH HEAVY BOXES\n\
					  PRESS S TO TOGGLE AN OBJECT DYNAMIC STATE", 
					  editorState,
					  gRunPhysics ? "ON" : "PAUSED", 
					  gDrawAABBs ? "ON" : "OFF", 
					  gCollisionSystem.mDynamicBodies.size(), gCollisionSystem.mStaticBodies.size(), 
					  gCollisionSystem.mCollisionIterations, gCollisionSystem.mCollisionsThisFrame, (f32)gAEFrameTime);
	AEGfxPrint(0, 0, 0xFFFFFFFF, buffer);

	//
	//	RENDER OBJECTS
	//
	gObjMgr.Render(&gCamera.GetWorldToCam());
	if (gDrawAABBs)
		DrawAABBs();

	//
	// RENDER GUI
	//
	if (gEditorState == eSelect || 
		((gEditorState == eCreateBox || gEditorState == eCreateCircle) && AEInputMousePressed(AE_MOUSE_LEFT)))
	{
		auto startWorld = gCamera.ConvertPointToWorld(gPickStart);
		auto endWorld = gCamera.ConvertPointToWorld(gPickEnd);
		auto size = endWorld - startWorld;
		auto mid = startWorld + size * 0.5f;
		u32 color = gEditorState == eSelect ? 0xFFFAAAAA : AEGfxColInterp(0xFFFF0A0A, 0xFFFFFFFF, AERandFloat());

		AEGfxReset();
		AEGfxSetTransform(&gCamera.GetWorldToCam());
		if (gEditorState == eCreateCircle)
			AEGfxCircle(mid.x, mid.y, size.x * 0.5f, color);
		else
			AEGfxRect(mid.x, mid.y, 0.0f, size.x, size.y, color);
		AEGfxFlush();
	}

	if (gEditorState == eTransforming)
	{
		AEGfxReset();
		AEGfxSetTransform(&gCamera.GetWorldToCam());
		// convert radius to match win coords
		f32 radius = gGizmoRadius *gCamera.mTransform.mScale.x;
		// render a circle for the gizmo hotspot
		AEGfxCircle(gGizmo.mPosition.x, gGizmo.mPosition.y, radius, 0xFFFF0E0E);
		AEGfxRect(gGizmo.mPosition.x, gGizmo.mPosition.y,0, gGizmo.mScale.x, gGizmo.mScale.y, 0xFFFFAAFF);
		AEGfxFlush();
	}

	// 
	// HIGHLIGHT SELECTED OBJECTS
	//

	AEGfxReset();
	AEGfxSetTransform(&gCamera.GetWorldToCam());
	for (auto it : gSelectedObjects)
	{
		if (RigidBody * body = dynamic_cast<RigidBody*>(it))
		{
			Vector2 aabbPos, aabbSize;
			body->ComputeAABB(&aabbPos, &aabbSize);
			AEGfxRect(aabbPos.x, aabbPos.y, 0.0f, aabbSize.x, aabbSize.y, 0xFFFFFF00);
		}
	}
	AEGfxFlush();
}
void Sandbox_Free()
{
	gCollisionSystem.ClearBodies();
	gObjMgr.FreeAllObjects();
	gSelectedObjects.clear();
}

void Sandbox_Unload()
{
}

// -- level 1
namespace Sandbox
{
	void CamInit()
	{
		gCamera = Camera();
	}
	void CamUpdate()
	{
		// zoom
		f32 zoom_speed = -0.1f;
		gCamera.mTransform.mScale *= (1 + AEInputGetMouseWheel()*zoom_speed);
		if (AEInputMousePressed(AE_MOUSE_MIDDLE))
		{
			gCamera.mTransform.mPosition -= gAEMouseMovement * gCamera.mTransform.mScale.x;
		}
	}

	void AutoComputeBodyInvMass(RigidBody * body)
	{
		f32 magic_density = 0.00658f;
		body->mInvMass = 1.0f / (body->mScale.x * body->mScale.y * magic_density);
	}
	void KeyboardInput()
	{
		if (AEInputKeyPressed(VK_OEM_PLUS))
		{
			gInitObjCount += 1;
			gAEGameStateNext = AE_GS_RESTART;
		}
		if (AEInputKeyPressed(VK_OEM_MINUS))
		{
			if (gInitObjCount)
				gInitObjCount -= 1;

			gAEGameStateNext = AE_GS_RESTART;
		}

		//
		// Simulation Control
		// 
		if (AEInputKeyTriggered('P'))
			gRunPhysics = !gRunPhysics;
		if (AEInputKeyPressed('I'))
		{
			gCollisionSystem.mCollisionIterations += 1;
		}
		if (AEInputKeyPressed('O'))
		{
			if (gCollisionSystem.mCollisionIterations > 1)
				gCollisionSystem.mCollisionIterations -= 1;
		}

		// Object creation

		if (AEInputKeyTriggered(VK_SPACE))
		{
			if (AEInputKeyPressed(AE_KEY_SHIFT))
			{
				RigidBody * box = CreateRandBoxWithMass(50.0f, gGravity);
				box->mPosition = Vector2(300, 0);
				box->mVelocity = Vector2(-1000.0f, 0.0f);
				box->mCollisionShape = CSHAPE_OBB;
			}
			else
			{
				RigidBody * box = CreateRandBoxWithMass(15.0f, gGravity);
				box->mPosition = Vector2(0, 300);
				box->mVelocity = Vector2(0, -1000.0f);
				box->mCollisionShape = CSHAPE_OBB;
			}
		}

		// deleting object
		if (AEInputKeyTriggered(VK_DELETE))
		{
			while (gSelectedObjects.size())
			{
				RigidBody * body = dynamic_cast<RigidBody*>(gSelectedObjects.back());
				gCollisionSystem.RemoveRigidBody(body);
				gObjMgr.DestroyObject(body);
				gSelectedObjects.pop_back();
				gEditorState = eIdle;
			}
		}

		if (AEInputKeyTriggered('S'))
		{
			for (auto it : gSelectedObjects)
			{
				RigidBody * body = dynamic_cast<RigidBody*>(it);

				// remove from collision system 
				gCollisionSystem.RemoveRigidBody(body);

				// make dynamic and add back to collision system
				if (FLOAT_ZERO(body->mInvMass))
				{
					// set mass (area times density)
					AutoComputeBodyInvMass(body);
					gCollisionSystem.AddRigidBody(body, true);
				}
				else { // Make static and add back to collision system
					body->mInvMass = 0.0f;
					gCollisionSystem.AddRigidBody(body, false);
				}
			}
		}

		if (AEInputKeyPressed('Q') && gEditorState != eCreateBox)
			gEditorState = eCreateBox;
		else if (!AEInputKeyPressed('Q') && gEditorState == eCreateBox)
			gEditorState = eIdle;
		if (AEInputKeyPressed('W') && gEditorState != eCreateCircle)
			gEditorState = eCreateCircle;
		else if (!AEInputKeyPressed('W') && gEditorState == eCreateCircle)
			gEditorState = eIdle;
	}
	Transform2D ComputeLocalFromWorld(const Transform2D & world, const Transform2D & parent)
	{
		Transform2D local;
		local.mOrientation = world.mOrientation - parent.mOrientation;
		local.mScale = Vector2(world.mScale.x / parent.mScale.x, world.mScale.y / parent.mScale.y);

		f32 cosP = cosf(parent.mOrientation), sinP = sinf(parent.mOrientation);
		auto & s = parent.mScale;
		auto & p = parent.mPosition;
		auto & wp = world.mPosition;

		local.mPosition.x = (wp.x - p.x) * cosP / s.x + (wp.y - p.y) * sinP / s.x;
		local.mPosition.y = -(wp.x - p.x) * sinP / s.y + (wp.y - p.y) * cosP / s.y;

		return local;
	}
	std::vector<Transform2D> localToGizmos;
	void ComputeLocalTransforms(const OBJECT_PTR_LIST & objects)
	{
		localToGizmos.clear();
		for (auto go : objects)
		{
			Transform2D local = ComputeLocalFromWorld(Transform2D(go->mPosition, go->mScale, go->mRotation), gGizmo);
			localToGizmos.push_back(local);
		}
	}
	void UpdateGizmoArea(const OBJECT_PTR_LIST & selectedObjects)
	{
		if (selectedObjects.size()) // check that we actually have an object selected
		{
			Vector2 minP = { FLT_MAX, FLT_MAX };
			Vector2 maxP = { -FLT_MAX, -FLT_MAX };

			// loop and compute aabb and center point for all
			for (auto go : selectedObjects)
			{
				if (RigidBody * body = dynamic_cast<RigidBody*>(go))
				{
					Vector2 aabb_pos, aabb_size, aabb_min, aabb_max;
					body->ComputeAABB(&aabb_pos, &aabb_size);
					aabb_min = aabb_pos - aabb_size * 0.5f;
					aabb_max = aabb_pos + aabb_size * 0.5f;

					if (minP.x > aabb_min.x) minP.x = aabb_min.x;
					if (minP.y > aabb_min.y) minP.y = aabb_min.y;
					if (maxP.x < aabb_min.x) maxP.x = aabb_min.x;
					if (maxP.y < aabb_min.y) maxP.y = aabb_min.y;

					if (minP.x > aabb_max.x) minP.x = aabb_max.x;
					if (minP.y > aabb_max.y) minP.y = aabb_max.y;
					if (maxP.x < aabb_max.x) maxP.x = aabb_max.x;
					if (maxP.y < aabb_max.y) maxP.y = aabb_max.y;
				}
			}

			// gizmo center is the center of the total AABB
			gGizmo.mPosition = minP + (maxP - minP) * 0.5f;
			gGizmo.mScale = (maxP - minP);
			gGizmo.mOrientation = 0.0f;
		}
	}
	void EditorInput()
	{
		KeyboardInput();

		// input variables (used in many cases).
		u8 mouseLeft = AEInputMousePressed(AE_MOUSE_LEFT);
		u8 mouseRight = AEInputMousePressed(AE_MOUSE_RIGHT);
		u8 mouseLeftTrig = AEInputMouseTriggered(AE_MOUSE_LEFT);
		u8 mouseRightTrig = AEInputMouseTriggered(AE_MOUSE_RIGHT);
		u8 shift = AEInputKeyPressed(AE_KEY_SHIFT);
		u8 alt = AEInputKeyPressed(AE_KEY_ALT);
		u8 ctrl = AEInputKeyPressed(AE_KEY_CTRL);
		Vector2 mouseW = gCamera.ConvertPointToWorld(gAEMousePosition);

		if (AEInputKeyTriggered('L'))
			gDrawAABBs = !gDrawAABBs;

		// on mouse triggered an
		switch (gEditorState)
		{
		case eSelect:
		case eIdle:{

			// new click
			if (mouseLeftTrig)
			{
				// pick objects (if anything is selected)
				gPickStart = gPickEnd = gAEMousePosition;
				gEditorState = eSelect;
			}
			// multiple selection
			else if (mouseLeft)
			{
				gPickEnd = gAEMousePosition;
			}
			else if (!mouseLeft && gEditorState == eSelect)
			{
				// pick objects
				auto picked = PickObjects(gPickStart, gPickEnd);

				// + SHIFT --> add to selection
				if (shift && picked.size()){
					for (auto it : picked){
						gSelectedObjects.remove(it);
						gSelectedObjects.push_back(it);
					}
					gEditorState = eTransforming;
				}
				else if (!shift && picked.size()){
					gSelectedObjects = picked;
					gEditorState = eTransforming;
				}

				// didn't cliked anything and not pressing shift --> unselect
				else if (!shift && picked.empty()){
					gSelectedObjects.clear();
					gEditorState = eIdle;
				}

				// update the area of the gizmo
				UpdateGizmoArea(gSelectedObjects);

				// Compute Locals
				ComputeLocalTransforms(gSelectedObjects);
			}
		}break;
		case eTransforming:{

			// variables
			static Transform2D origTransform;
			static Vector2 velStartPos;
			
			// update the area of the gizmo, but DON't update locals
			UpdateGizmoArea(gSelectedObjects);
			
			// First-click logic
			if (mouseLeftTrig || mouseRightTrig)
			{
				// check if the gizmo is selected
				f32 radius = gGizmoRadius* gCamera.mTransform.mScale.x;
				gbGizmoSelected = StaticRectToStaticCirlce(&mouseW, 2, 2, &gGizmo.mPosition, radius);

				// if we're not clicking on the gizmo , then go back to select
				if (!gbGizmoSelected){
					gEditorState = eIdle;
					break;
				}

				// save transform state before action is applied
				origTransform = gTranformMod = gGizmo;

				// compute locals for the selected objects
				ComputeLocalTransforms(gSelectedObjects);

				// keep track of mouse movements
				gPickStart = gPickEnd = mouseW;

				// save the position of the first time 
				// we're activating the velocity modifier.
				if (shift)
					velStartPos = gPickEnd;

			}

			// gizmo is selected and we're doing something with it. 
			if (gbGizmoSelected)
			{
				gPickEnd = mouseW;
				Vector2 mouseMoveW = gPickEnd - gPickStart;
				Transform2D prevTransform = gTranformMod;

				#pragma region gizmo input
				// center hotspot
				if (mouseLeft)
				{
					// save the position of the first time 
					// we're activating the velocity modifier.
					if (AEInputKeyTriggered(AE_KEY_SHIFT))
						velStartPos = gPickEnd;

					if (alt && shift)
						gTranformMod.mScale.x = origTransform.mScale.x + mouseMoveW.x;
					else if (alt && ctrl)
						gTranformMod.mScale.y = origTransform.mScale.y + mouseMoveW.y;
					else if (alt)
						gTranformMod.mScale = origTransform.mScale + mouseMoveW;
					else if (shift)
						gTranformMod.mPosition = origTransform.mPosition + (velStartPos - gPickStart);
					else
						gTranformMod.mPosition = origTransform.mPosition + mouseMoveW;

				}
				if (mouseRight)
				{
					f32 mouseMoveToAngle = TWO_PI * 0.01f / gCamera.mTransform.mScale.x;
					gTranformMod.mOrientation = origTransform.mOrientation + mouseMoveW.y * mouseMoveToAngle;
				}
				#pragma endregion

				#pragma region object transform modification
				
				if(gSelectedObjects.size())
				{
					printf("pos diff is %.2, %.2f\n", gGizmo.mPosition.x - prevTransform.mPosition.x, gGizmo.mPosition.y - prevTransform.mPosition.y);
					printf("rot diff is %.2f\n", gGizmo.mOrientation - prevTransform.mOrientation);

					// loop and apply changes to all game objects
					u32 i = 0; 
					for (auto go : gSelectedObjects)
					{
						Transform2D world = gTranformMod * localToGizmos[i];
						go->mPosition = world.mPosition;
						go->mScale = world.mScale;
						go->mRotation = world.mOrientation;

						go->mPosition += gTranformMod.mPosition - prevTransform.mPosition;
						go->mScale += gTranformMod.mScale - prevTransform.mScale;
						go->mRotation += gTranformMod.mOrientation - prevTransform.mOrientation;

						// velocity modification (propelling)
						if (!mouseLeft && shift && !alt)
						{
							RigidBody * body = dynamic_cast<RigidBody*>(go);
							body->mVelocity = (gPickEnd - velStartPos) * 3.0f;// (gGizmo.mPosition - origTransform.mPosition);
							gbGizmoSelected = false;
						}

						// increment counter
						++i;
					}

				}
				#pragma endregion

				// velocity modification draw
				if (shift && !alt)
					AEGfxLine(velStartPos.x, velStartPos.y, 0, 0xFFFFFF00, gPickEnd.x, gPickEnd.y, 0, 0xFFFFFF00);
				
			}
		}break;
		case eCreateBox:
		case eCreateCircle:
		{
			static bool bDrawingNewShape = false;

			// new click
			if (mouseLeftTrig)
			{
				// pick objects (if anything is selected)
				if (PickObjects(gPickStart).size())
					gEditorState = eTransforming;

				gPickStart = gPickEnd = gAEMousePosition;
				bDrawingNewShape = true;
			}
			// multiple selection
			else if (mouseLeft)
			{
				gPickEnd = gAEMousePosition;
			}
			else if (bDrawingNewShape)
			{
				auto startWorld = gCamera.ConvertPointToWorld(gPickStart);
				auto endWorld = gCamera.ConvertPointToWorld(gPickEnd);
				auto size = endWorld - startWorld;
				auto mid = startWorld + size * 0.5f; size.x = fabs(size.x); size.y = fabs(size.y);

				// sanity check, no zero size rigid body
				if (FLOAT_ZERO(size.x) || FLOAT_ZERO(size.y)){
					bDrawingNewShape = false;
					break;
				}
				
				RigidBody * body = NULL;
				if (gEditorState == eCreateBox){
					body = CreateRandBoxWithMass(1.0f, gGravity);
					body->mScale = size;
				}
				else{
					body = CreateRandCircleWithMass(1.0f, gGravity);
					body->mScale = size*0.5f;
				}
				body->mPosition = mid;
				AutoComputeBodyInvMass(body);
				gCollisionSystem.RemoveRigidBody(body);
				gCollisionSystem.AddRigidBody(body, true);
				bDrawingNewShape = false;
				gEditorState = eIdle;
			}
		}

		}// end switch(gEditor)
	}

	OBJECT_PTR_LIST PickObjects(const Vector2 & start)
	{
		OBJECT_PTR_LIST picked;
		
		// convert point to world
		Vector2 pickedWorld = gCamera.ConvertPointToWorld(start);

		auto objects = gObjMgr.GetAliveObjects();
		for (auto it : objects)
		{
			if (RigidBody * body = dynamic_cast<RigidBody*>(it))
			{
				switch (body->mCollisionShape)
				{
				case CSHAPE_AABB:
				case CSHAPE_OBB:{
					Transform2D tr = { body->mPosition, body->mScale, body->mRotation };
					if (StaticPointToOrientedRect(&pickedWorld, &tr.mPosition, tr.mScale.x, tr.mScale.y, tr.mOrientation))
						picked.push_back(body);
				}break;
				case CSHAPE_CIRCLE:{
					if (StaticPointToStaticCircle(&pickedWorld, &Vector2(body->mPosition), body->mScale.x))
						picked.push_back(body);
				}break;
				}
			}
		}

		return picked;
	}
	OBJECT_PTR_LIST PickObjects(const Vector2 & start, const Vector2 & end)
	{
		OBJECT_PTR_LIST picked;

		// convert multi-select to an AABB in world
		Vector2 startWorld = gCamera.ConvertPointToWorld(gPickStart);
		Vector2 endWorld = gCamera.ConvertPointToWorld(gPickEnd);
		Vector2 size = endWorld - startWorld; 
		Vector2 mid = startWorld + size * 0.5f;
		size.x = fabsf(size.x); size.y = fabsf(size.y);

		auto objects = gObjMgr.GetAliveObjects();
		for (auto it : objects)
		{
			if (RigidBody * body = dynamic_cast<RigidBody*>(it))
			{
				switch (body->mCollisionShape)
				{
					case CSHAPE_AABB:
					{
						Transform2D tr1 = { mid, size, 0.0f };
						Transform2D tr2 = { body->mPosition, body->mScale, body->mRotation };
						if (OrientedRectToOrientedRectEx(&tr1, &tr2, NULL))
							picked.push_back(body);
					}
					case CSHAPE_OBB:{
						Transform2D tr1 = { mid, size, 0.0f };
						Transform2D tr2 = { body->mPosition, body->mScale, body->mRotation };
						if (OrientedRectToOrientedRectEx(&tr1, &tr2,NULL))
							picked.push_back(body);
					}break;
					case CSHAPE_CIRCLE:{
						if (StaticRectToStaticCirlce(&mid, size.x, size.y, &Vector2(body->mPosition), body->mScale.x))
							picked.push_back(body);
					}break;
				}
			}
		}

		return picked;
	}

	void DrawAABBs()
	{
		AEGfxReset();
		AEGfxSetTransform(&gCamera.GetWorldToCam());
		auto objects = gObjMgr.GetAliveObjects();
		for (auto it : objects)
		{
			if (RigidBody * body = dynamic_cast<RigidBody*>(it))
			{
				Vector2 aabbPos, aabbSize;
				body->ComputeAABB(&aabbPos, &aabbSize);
				AEGfxRect(aabbPos.x, aabbPos.y, 0.0f, aabbSize.x, aabbSize.y, 0xFF10FFFF);
			}
		}
		AEGfxFlush();
	}
}
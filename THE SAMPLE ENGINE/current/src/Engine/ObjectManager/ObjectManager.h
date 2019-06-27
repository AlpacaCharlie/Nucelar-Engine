// ---------------------------------------------------------------------------
// Project Name		:	Just Defend
// File Name		:	ObjectManager.h
// Author			:	Javier Gome
// Creation Date	:	2019/01/28
// Purpose			:	Header for Object Manager - This is the first implementation 
//						for the ObjectManager
// --------------------------------------------------------------------------
#ifndef GAME_OBJECT_MGR_H_
#define GAME_OBJECT_MGR_H_

#include "GameObjectGodFather.h"
#include <chrono>

#define MAX_GAME_OBJECT_NUM  1024

class ObjectManager
{
public:
	void			Initialize();	// Initializes the game object manager
	void			Update();		// updates all the alive and active game objects.
	void			Render();		// render all the visible game objects.
	virtual void	Render(AEMtx33 * camMtx); // NEW in lab 6: renders the visible game objects with a camera
	virtual void	RenderHUD(AEMtx33 * camMtx); // NEW in lab 6: renders the visible game objects with a camera
	void			Shutdown();		// destroy all the object and prints an error if there are alive objects
	void CountObject();
									// Adding an object - we will assume that 
	GameObject *	AddObject(GameObject * newObj); // creates a new empty object
	GameObject *	AddObject(GameObject * newObj, f32 x, f32 y, f32 sx, f32 sy, f32 rot, AEGfxTriList * pMesh = NULL, AEGfxTexture * pTex = NULL, int z = 0);
	GameObject *    FindObject(const char* name);
	// Destroy Objects
	void			DestroyObject(GameObject * pObj);	// places an object onto the destroyed list.
	void			FreeAllObjects();					// deletes all the objects right away. 

	// returns a const reference to the alive list (cannot modify)
	const OBJECT_PTR_LIST & 	GetAliveObjects();

	void FreeDestroyedObjects();
	OBJECT_PTR_LIST mHUDobjects;
	OBJECT_PTR_LIST mHUDobjects2;
	OBJECT_PTR_LIST mAliveObjects;
	OBJECT_PTR_LIST mAliveObjects2;
	OBJECT_PTR_LIST mAliveObjects3;
	OBJECT_PTR_LIST mAliveObjects4;
	OBJECT_PTR_LIST mAliveObjects5;
	OBJECT_PTR_LIST mAliveObjectsList[7] = { mAliveObjects,
		mAliveObjects2,
		mAliveObjects3,
		mAliveObjects4,
		mAliveObjects5,
		mHUDobjects ,
		mHUDobjects2 };
private:
	void RemoveObjectFromAliveList(GameObject * pObj);

	u32				mIdGenerator;
	
	OBJECT_PTR_LIST mDestroyedObjects;

};

extern ObjectManager gObjMgr;

#endif 
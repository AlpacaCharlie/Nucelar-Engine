// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	ObjectManager.h
// Author			:	Thomas Komair
// Creation Date	:	2015/02/04
// Purpose			:	Header for Object Manager - This is the first implementation 
//						for the ObjectManager
// ---------------------------------------------------------------------------
#ifndef GAME_OBJECT_MGR_H_
#define GAME_OBJECT_MGR_H_
// ---------------------------------------------------------------------------
#include "GameObject.h"

#define MAX_GAME_OBJECT_NUM  1024

class ObjectManager
{
public:
	void			Initialize();	// Initializes the game object manager
	void			Update();		// updates all the alive and active game objects.
	void			Render();		// render all the visible game objects.
	void			Render(AEMtx33 * camMtx); // NEW in lab 6: renders the visible game objects with a camera
	void			Shutdown();		// destroy all the object and prints an error if there are alive objects

	// Adding an object - we will assume that 
	GameObject *	AddObject(GameObject * newObj, const char * name); // creates a new empty object
	GameObject *	AddObject(GameObject * newObj, const char* name, f32 x, f32 y, f32 sx, f32 sy, f32 rot, AEGfxTriList * pMesh = NULL, AEGfxTexture * pTex = NULL);

	// Destroy Objects
	void			DestroyObject(GameObject * pObj);	// places an object onto the destroyed list.
	void			FreeAllObjects();					// deletes all the objects right away. 

	// Get Object
	GameObject *	FindObject(u32 id);
	GameObject *	FindObject(const char* name);
	void			FindObject(const char* name, std::list<GameObject *> & objects);

	// returns a const reference to the alive list (cannot modify)
	const OBJECT_PTR_LIST & 	GetAliveObjects();
	
private:
	void FreeDestroyedObjects();
	void RemoveObjectFromAliveList(GameObject * pObj);

	u32				mIdGenerator; 
	OBJECT_PTR_LIST mAliveObjects;
	OBJECT_PTR_LIST mDestroyedObjects;
};

// Global and unique object manager. No other object manager should be created. 
extern ObjectManager 	gObjMgr;

// ---------------------------------------------------------------------------
#endif
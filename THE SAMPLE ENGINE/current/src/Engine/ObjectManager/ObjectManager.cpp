// ---------------------------------------------------------------------------
// Project Name		:	Just Defend
// File Name		:	ObjectManager.cpp
// Author			:	Javier Gomez
// Creation Date	:	2019/01/28
// Purpose			:	Implementation file for Object Manager - This is the first implementation 
//						for the ObjectManager
// ---------------------------------------------------------------------------
#include <AEEngine.h>
#include "ObjectManager.h"
#include <chrono>
#include <iostream>

ObjectManager 	gObjMgr;
int CountObjects = 0;
void			ObjectManager::Initialize()
{
	mIdGenerator = 0;
	for (int j = 0 ; j < 7; j++)
	{
		for (GameObject* i : gObjMgr.mAliveObjectsList[j])
		{
			if (i->mbActive && i->mbAlive)
			{
				i->Initialize();
			}
		}
	}
}

void			ObjectManager::Shutdown()
{
	FreeAllObjects();
}


struct ZCompare
{
	// expected to act as a LESS THAN operator
	bool operator()(GameObject * & lhs, GameObject * rhs)
	{
		return lhs->Z_Axis < rhs->Z_Axis;
	}
};

void ObjectManager::CountObject()
{
	for (int i = 0; i < 7; i++)
	{
		CountObjects += (int)gObjMgr.mAliveObjectsList[i].size();
	}

	//std::cout << "Objects Count : " << CountObjects << std::endl;
	CountObjects = 0;
}

//Goes through all the alive and active objects and updates them
void			ObjectManager::Update()
{
	FreeDestroyedObjects();

	
	for (int j = 0; j < 7; j++)
	{
		for (GameObject* i : gObjMgr.mAliveObjectsList[j])
		{
			if (i->mbActive && i->mbAlive)
			{
				i->Update();
			}
		}
	}
}

// Render:	Render all the alive AND visible game objects.
void			ObjectManager::Render()
{
	for (int j = 0; j < 5; j++)
	{
		for (GameObject* i : gObjMgr.mAliveObjectsList[j])
		{
			if (i->mbVisible && i->mbAlive)
			{
				i->Render();
			}
		}
	}
}

void  ObjectManager::Render(AEMtx33 * camMtx)
{
	if (camMtx)//if the matrix isnt null
	{
		for (int j = 0; j < 5; j++)
		{
			for (GameObject* i : gObjMgr.mAliveObjectsList[j])
			{
				if (i->mbVisible && i->mbAlive)
				{
					i->Render(camMtx);
				}
			}
		}
	}
}
void  ObjectManager::RenderHUD(AEMtx33 * camMtx)
{
	if (camMtx)//if the matrix isnt null
	{
		for(int u = 5 ; u <7 ; u++)
		{
			for (GameObject* i : gObjMgr.mAliveObjectsList[u])
			{
				if (i && i->mbVisible && i->mbAlive)
				{
					i->Render(camMtx);
				}
			}
		}
	}
}

GameObject *	ObjectManager::FindObject(const char* name)
{
	for (int j = 0; j < 7; j++)
	{
		for (GameObject* i : gObjMgr.mAliveObjectsList[j])
		{
			if (i->mName == name)
			{
				return i;
			}
		}
	}
	return NULL;
}
// AddObject:	Adds the specified game object with default values:
//				mPosition to (0,0), mScale to (1,1), mRotation to 0
//				mpMesh and mpTex to NULL
GameObject *	ObjectManager::AddObject(GameObject * newObj)
{
	return AddObject(newObj, 0, 0, 1, 1, 0, NULL, NULL);
}

// AddObject:	Adds the specified game object with the specified values:
//				Make sure that the object you are adding is valid (i.e. it's not NULL)
//				Set it to active, alive and visible.
//				Add it to the alive list (use the std::list push_back() to do so). 
//				Call Initialize on the new object (after it has been added to the alive list).
GameObject *	ObjectManager::AddObject(GameObject * newObj, f32 x, f32 y, f32 sx, f32 sy, f32 rot, AEGfxTriList * pMesh, AEGfxTexture * pTex, int z)
{

	if (newObj == 0)
		return NULL;

	if (z > 6)
	{
		Beep(523, 500);
		return NULL;
	}

	newObj->Id = std::chrono::duration_cast< std::chrono::milliseconds >(
		std::chrono::system_clock::now().time_since_epoch()
		);
	newObj->mPosition.x = x;
	newObj->mPosition.y = y;
	newObj->mScale.x = sx;
	newObj->mScale.y = sy;
	newObj->mRotation = rot;
	newObj->mpMesh = pMesh;
	newObj->mpTex = pTex;

	newObj->mbActive = true;
	newObj->mbAlive = true;
	newObj->mbVisible = true;

	newObj->Initialize();

	newObj->Z_Axis = z;

	gObjMgr.mAliveObjectsList[z].push_front(newObj);
	
	return newObj;
}

// DestroyObject:	Prepares an object for destruction
//					1. Set the object mbAlive flag to false
//					2. Add it to the destroyed objects list. You can use the 
//					std::list push_back() or push_front() functions to do so. 
//	IMPORTANT: DO NOT FREE THE MEMORY AT THIS POINT!
void			ObjectManager::DestroyObject(GameObject * pObj)
{
	pObj->mbAlive = false;
	gObjMgr.mDestroyedObjects.push_back(pObj);
}

// FreeAllObjects:	Destroys all objects right away
void			ObjectManager::FreeAllObjects()
{
	FreeDestroyedObjects();
	GameObject * pGO;

	for (int j = 0; j < 7; j++)
	{
		while (gObjMgr.mAliveObjectsList[j].empty() == false)
		{
			pGO = gObjMgr.mAliveObjectsList[j].back();
			delete pGO;
			gObjMgr.mAliveObjectsList[j].pop_back();
		}
	}
}

// GetObject:	Returns a const reference to the alive list (cannot modify)
const std::list<GameObject*> & 	ObjectManager::GetAliveObjects()
{
	return mAliveObjects;
}

void ObjectManager::RemoveObjectFromAliveList(GameObject * pObj)
{
	for (int j = 0; j < 7; j++)
	{
		mAliveObjectsList[j].remove(pObj);
	}
}

void ObjectManager::FreeDestroyedObjects()
{
	GameObject * pGO;

	while (gObjMgr.mDestroyedObjects.empty() == false)
	{
		pGO = gObjMgr.mDestroyedObjects.back();
		RemoveObjectFromAliveList(pGO);
		gObjMgr.mDestroyedObjects.pop_back();
		delete pGO;
	}
}

#include "../AEX/AEXRtti.h"
#include "../AEX/AEXBase.h"
#include "NComponent.h"
#include "NGameObject.h"
#include "NObjectManager.h"
#include <stdio.h>

// ---------------------------------------------------------------------------
// Initialize:
void NObjectManager::Initialize()
{

}

// ---------------------------------------------------------------------------
// Update:
void NObjectManager::Update()
{
	FreeDestroyedObjects();
}

// ---------------------------------------------------------------------------
// Shutdown:
void NObjectManager::Shutdown()
{
	FreeAllObjects();
}

// ---------------------------------------------------------------------------
// AddGameObject:
NGameObject * NObjectManager::AddGameObject(NGameObject * newObj, const char * name)
{
	if (newObj)
	{
		// Change its values to all the given parameters
		newObj->SetName(name);
		newObj->mbAlive = true;

		// Push it to the back of the list
		mAliveObjects.push_back(newObj);

		// The object is ready, initialize it.
		newObj->Initialize();

		printf("NEW OBJECT CREATED\n");

		return newObj;
	}
	return NULL;
}

// ---------------------------------------------------------------------------
// DestroyObject:
void NObjectManager::DestroyObject(NGameObject * pObj)
{
	if (pObj)
	{
		// Set its alive flag to false
		pObj->mbAlive = false;

		// Push it to the back of the Detroyed Objects list
		mDestroyedObjects.push_back(pObj);
	}
}

// ---------------------------------------------------------------------------
// FreeAllObjects:
void NObjectManager::FreeAllObjects()
{
	FreeDestroyedObjects();

	// While the list is not empty
	while (!mAliveObjects.empty())
	{
		// Destroy the object in the back of the list and pop it back.
		DestroyObject(mAliveObjects.back());
		mAliveObjects.pop_back();
	}
}

NGameObject * NObjectManager::FindObject(u32 id)
{
	// Create "it" to iterate through the list
	GO_LIST::iterator it;

	if (!mAliveObjects.empty())
	{
		// Iterate through every member of the list until reaching the end
		for (it = mAliveObjects.begin(); it != mAliveObjects.end(); it++)
		{
			// Pointer pointing to the lists' GameObjects
			NGameObject * pointer = *it;

			// if the ID is the same, return it
			if (pointer->GetUID() == id)
				return pointer;
		}
	}
	return NULL; // not found
}

// ---------------------------------------------------------------------------
// FindObject:
NGameObject * NObjectManager::FindObject(const char * name)
{
	// Create "it" to iterate through the list
	GO_LIST::iterator it;

	if (!mAliveObjects.empty())
	{
		// Iterate through every member of the list until reaching the end
		for (it = mAliveObjects.begin(); it != mAliveObjects.end(); it++)
		{
			// Pointer pointing to the lists' GameObjects
			NGameObject * pointer = *it;

			// if the name is the same, return it
			if (pointer->GetName() == name)
				return pointer;
		}
	}
	return NULL; // not found
}

NGameObject * NObjectManager::FindObject(const char * name, std::list<NGameObject*>& objects)
{

	// Create "it" to iterate through the list
	GO_LIST::iterator it;
	if (!objects.empty())
	{
		// Iterate through every member of the list until reaching the end
		for (it = objects.begin(); it != objects.end(); it++)
		{
			// Pointer pointing to a list of your desire
			NGameObject * pointer = *it;

			// if the name is the same, return it
			if (pointer->GetName() == name)
				return pointer;
		}
	}
	return NULL; // not found
	
}



const GO_LIST & NObjectManager::GetAliveObjects()
{
	return mAliveObjects;
}

// ---------------------------------------------------------------------------
// FreeDestroyedObjects:
void NObjectManager::FreeDestroyedObjects()
{
	// Create "it" to iterate through the list
	GO_LIST::iterator it;

	if (!mDestroyedObjects.empty())
	{
		// Iterate through every member of the list until reaching the end
		for (it = mDestroyedObjects.begin(); it != mDestroyedObjects.end(); it++)
		{
			// Pointer pointing to the lists' GameObjects
			NGameObject * pointer = *it;

			// Remove the GameObject from the Alive Objects list
			mAliveObjects.remove(pointer);

			// Delete it
			delete pointer;
		}

		// Clear the destroyed objects list
		mDestroyedObjects.clear();
	}

}

// ---------------------------------------------------------------------------
// RemoveObjectFromAliveList
void NObjectManager::RemoveObjectFromAliveList(NGameObject * pObj)
{
	mAliveObjects.remove(pObj);
}

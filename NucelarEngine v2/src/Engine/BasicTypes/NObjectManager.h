#pragma once
#include "../AEX/AEXRtti.h"
#include "../AEX/AEXBase.h"
#include "NComponent.h"
#include "NGameObject.h"
using namespace AEX;

class  NObjectManager : public IBase
{
public:
	// Basic functions
	void Initialize();
	void Update();
	void Shutdown();

	// Add a new gameobject
	NGameObject * AddGameObject(NGameObject * newObj, const char * name);

	// places an object onto the destroyed list.
	void	DestroyObject(NGameObject * pObj);

	// deletes all the objects right away. 
	void	FreeAllObjects();

	// Finds a GameObjeect
	NGameObject *	FindObject(u32 id);
	NGameObject *	FindObject(const char* name);
	NGameObject *	FindObject(const char* name, std::list<NGameObject *> & objects);

	const GO_LIST & GetAliveObjects();

private:
	void FreeDestroyedObjects();
	void RemoveObjectFromAliveList(NGameObject * pObj);

	GO_LIST mAliveObjects;
	GO_LIST mDestroyedObjects;

};

extern NObjectManager 	gObjMgr;
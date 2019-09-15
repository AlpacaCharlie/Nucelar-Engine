#pragma once
#ifndef N_COMPONENT_H_
#define N_COMPONENT_H_
#include "../AEX/AEXCore.h"
using namespace AEX;
class IComp : public IBase
{
	AEX_RTTI_DECL(IComp, IBase);
	friend class NGameObject;

public:
	IComp();
	virtual ~IComp() = 0;

	bool IsEnabled();
	virtual void SetEnabled(bool enabled);
	virtual void Initialize();
	virtual void Update();
	virtual void Shutdown();

	//gameobject that has this component
	NGameObject * GetOwner(void);
//protected
public:
	NGameObject * mOwner; //owner object
	bool mbEnabled;
};
#endif
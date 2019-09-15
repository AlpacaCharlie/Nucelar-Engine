#pragma once
#include "../AEX/AEXRtti.h"
#include "../AEX/AEXBase.h"
#include "NComponent.h"
using namespace AEX;
class  NGameObject : public IBase
{
	AEX_RTTI_DECL(NGameObject, IBase);

public:
	NGameObject();
	virtual ~NGameObject();

	virtual void SetEnabled(bool enabled); //Component sleep
	virtual void Intialize(); //initializes every component
	virtual void ShutDown(); //frees stuff

	#pragma region// COMPONENT MANAGEMENT
	//Getters, decoment when component system gets created

	u32 GetCompCount() const;
	IComp * GetComp(u32 index)const;
	IComp * GetComp(const char * type)const;
	IComp * GetComp(const Rtti & type)const;
	IComp * GetCompName(const char * compName, const char *compType = NULL)const;
	void OnGui(); // I guess this is when it is on the scene
	template<class T>
	T* GetComp(const char * compName = NULL); //returns a component in the vector with this name

	template<class T>
	T* GetCompDerived(const char * compName = NULL);
	template<class T>
	T* NewComp(const char * compName = NULL);

	//Add and remove comps with pointer 
	IComp * AddComp(IComp * pComp);
	void RemoveComp(IComp * pComp);

	//Remove Components with name and type (1st encounter)
	void RemoveCompType(const char * compType);
	void RemoveCompType(const Rtti & compType);
	void RemoveCompName(const char * compName, const char * compType = NULL);

	void RemoveAllCompType(const char * compType);
	void RemoveAllCompType(const Rtti & compType);
	void RemoveAllCompName(const char * compName, const char * compType = NULL);

	
	
	//Remove comps
	void RemoveAllComp();

	// debug only!!
	std::vector<IComp*> &GetComps() { return mComps; }
	const std::vector<IComp*> &GetComps() const { return mComps; }
protected:
	//This comment would have the vector of comps
	std::vector<IComp*> mComps;
	bool mbEnabled;
};



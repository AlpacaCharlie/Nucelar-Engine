#include "NGameObject.h"
#include<string>
NGameObject::NGameObject() : IBase()
{
}

NGameObject::~NGameObject()
{
}

void NGameObject::SetEnabled(bool enabled)
{
	if (mbEnabled == enabled)
		return;
	mbEnabled = enabled;
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
		(*it)->SetEnabled(enabled);
}

void NGameObject::Intialize()
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
		(*it)->Initialize();
}

void NGameObject::ShutDown()
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
		(*it)->Shutdown();
}

u32 NGameObject::GetCompCount() const
{
	return mComps.size(); //WARNING
}

IComp * NGameObject::GetComp(u32 index) const
{
	if (index > GetCompCount())
		return NULL;
	return mComps[index];
}

IComp * NGameObject::GetComp(const char * type) const
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		std::string typeName = (*it)->GetType().GetName();
		if (typeName == type)
			return (*it);
	}
	return NULL;
}

IComp * NGameObject::GetComp(const Rtti & type) const
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		if ((*it)->GetType().IsExactly(type))
		{
			return (*it);
		}
	}
	return NULL;
}

IComp * NGameObject::GetCompName(const char * compName, const char * compType) const
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		if (strcmp((*it)->GetName(), compName) == 0)
		{
			if(compType && strcmp(compType,(*it)->GetType().GetName()) != 0)
				continue;
			return (*it);
		}
	}

	return nullptr;
}

void NGameObject::OnGui()
{
}
template<class T>
T * NGameObject::GetComp(const char * compName)
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		if ((*it)->GetType().IsExactly(T::TYPE()))
		{
			if ((*it)->GetType().IsExactly(T::TYPE()))
			{
				if(compName && strcmp(compName,(*it)->GetName()) != 0)
					continue;
				return (T*)(*it);
			}
		}
	}

	return NULL;
}
template<class T>
T * NGameObject::GetCompDerived(const char * compName)
{
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		if ((*it)->GetType().IsDerived(T::TYPE()))
		{
			if (compName && strcmp(compName, (*it)->GetName()) != 0)
				continue;
			return (T*)(*it);
		}
	}
	return NULL;
}
template<class T>
T * NGameObject::NewComp(const char * compName)
{
	T * newComp = new T;
	if (compName)
		NewComp->SetName(compName);
	return dynamic_cast<T*>(AddComp(NewComp))
}
IComp * NGameObject::AddComp(IComp * pComp)
{
	if (pComp)
	{
		pComp->mOwner = this;
		mComps.push_back(pComp);
	}
	return pComp;
}
void NGameObject::RemoveComp(IComp * pComp)
{
	if (!pComp)
		return;
	for (auto it = mComps.begin(); it != mComps.end(); ++it)
	{
		if ((*it) == pComp)
		{
			pComp->mOwner = NULL;
			mComps.erase(it);
			return;
		}
	}
}
void NGameObject::RemoveCompType(const char * compType)
{
	RemoveComp(GetComp(compType));
}

void NGameObject::RemoveCompType(const Rtti & compType)
{
	RemoveComp(GetComp(compType));
}

void NGameObject::RemoveCompName(const char * compName, const char * compType)
{
	RemoveComp(GetCompName(compName, compType));
}

void NGameObject::RemoveAllCompType(const char * compType)
{
	IComp * pComp = GetComp(compType);
	while (pComp)
	{
		RemoveComp(pComp);
		pComp = GetComp(compType);
	}
}

void NGameObject::RemoveAllCompType(const Rtti & compType)
{
	IComp * pComp = GetComp(compType);
	while ( pComp)
	{
		RemoveComp(pComp);
		pComp = GetComp(compType);
	}
}

void NGameObject::RemoveAllCompName(const char * compName, const char * compType)
{
	IComp * pComp = GetCompName(compName, compType);
	while (pComp)
	{
		RemoveComp(pComp);
		pComp = GetCompName(compName, compType);
	}
}

void NGameObject::RemoveAllComp()
{
	while (mComps.size())
	{
		mComps.back()->Shutdown();
		delete mComps.back();
		mComps.pop_back();
	}
}

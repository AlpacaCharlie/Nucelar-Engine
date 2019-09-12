#include "NGameObject.h"

NGameObject::NGameObject() : IBase()
{
}

NGameObject::~NGameObject()
{
}

void NGameObject::SetEnabled(bool enabled)
{
}

void NGameObject::Intialize()
{
}

void NGameObject::ShutDown()
{
}

void NGameObject::OnGui()
{
}
template<class T>
T * NGameObject::GetComp(const char * name)
{
	return nullptr;
}
template<class T>
T * NGameObject::GetCompDerived(const char * name)
{
	return NULL;
}
template<class T>
T * NGameObject::NewComp(const char * name)
{
	return nullptr;
}
void NGameObject::RemoveCompType(const char * compType)
{
}

void NGameObject::RemoveCompType(const Rtti & compType)
{
}

void NGameObject::RemoveCompName(const char * compName, const char * compType)
{
}

void NGameObject::RemoveAllComp()
{
}

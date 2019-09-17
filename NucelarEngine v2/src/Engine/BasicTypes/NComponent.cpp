#include "NComponent.h"

IComp::IComp() : mOwner(NULL), mbEnabled(true)
{
}

IComp::~IComp()
{
}

bool IComp::IsEnabled()
{
	return mbEnabled;
}

void IComp::SetEnabled(bool enabled)
{
	mbEnabled = enabled;
}
//these ones will get overriten
void IComp::Initialize()
{
}

void IComp::Update()
{
}

void IComp::Shutdown()
{
}

NGameObject * IComp::GetOwner(void)
{
	return mOwner;
}

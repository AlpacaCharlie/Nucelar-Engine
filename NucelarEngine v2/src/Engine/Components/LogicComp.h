#include "..\BasicTypes\NComponent.h"

class LogicComp : public IComp
{
public:

	virtual void Initialize();
	virtual void Update();
	virtual void Shutdown();


};
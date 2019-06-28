#pragma once
#ifndef DummyComp_H
#define DummyComp_H
using namespace AEX;
class DummyComp : public LogicComp
{
	AEX_RTTI_DECL(DummyComp, LogicComp);
public:
	DummyComp() : LogicComp() {}

[Property]
int x = 0;
int y = 0;
int z = 0;
[End]


	void Initialize() {
		LogicComp::Initialize();
		std::cout << "Dummy " << GetName() << " Initialize" << std::endl;
	}
	void Shutdown() {
		std::cout << "Dummy " << GetName() << " Shutdown" << std::endl;
		LogicComp::Shutdown();
	}
	void Update() {
		if (mbEnabled)
			std::cout << "Dummy " << GetName() << " Update" << std::endl;
	}
};

#endif // !DummyComp_H

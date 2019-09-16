#pragma once
#include "../AEX/AEXBase.h"
#include "../../Extern/glm/glm.hpp"
#include "../Color/Color.h"

class ISerializer : public AEX::IBase
{
public:
	ISerializer() {}
	virtual ~ISerializer() {}
	virtual void StreamRead(const char * name, s32 & out) {}
	virtual void StreamRead(const char * name, u32 & out) {}
	virtual void StreamRead(const char * name, f32 & out) {}
	virtual void StreamRead(const char * name, bool & out) {}
	virtual void StreamRead(const char * name, std::string & out) {}
	virtual void StreamRead(const char * name, glm::vec2 & out) {}
	virtual void StreamRead(const char * name, glm::vec3 & out) {}
	virtual void StreamRead(const char * name, Color & out) {}

	virtual void StreamWrite(const char * name, const s32 & out) {}
	virtual void StreamWrite(const char * name, const u32 & out) {}
	virtual void StreamWrite(const char * name, const f32 & out) {}
	virtual void StreamWrite(const char * name, const bool & out) {}
	virtual void StreamWrite(const char * name, const std::string & out) {}
	virtual void StreamWrite(const char * name, const glm::vec2 & out) {}
	virtual void StreamWrite(const char * name, const glm::vec3 & out) {}
	virtual void StreamWrite(const char * name, const Color & out) {}
};

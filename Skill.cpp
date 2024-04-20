#include "PCH.h"
#include "Skill.h"

// 持失切
Skill::Skill(const wstring& name) : name(name), caster(nullptr)
{
}

// 社瑚切
Skill::~Skill()
{
	caster = nullptr;
}
#include "PCH.h"
#include "Skill.h"

// 持失切
/*
Skill::Skill(const wstring& name, SKILL_CALLBACK callback) 
	: ID(nextID++), name(name), callback(callback)
{
}
*/

Skill::Skill(const wstring& name) : name(name)
{
}

// 社瑚切
Skill::~Skill()
{
}
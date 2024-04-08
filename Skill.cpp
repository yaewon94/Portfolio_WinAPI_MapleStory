#include "PCH.h"
#include "Skill.h"

// static 필드 초기화
UINT Skill::nextID = 0;

// 생성자
Skill::Skill(const wstring& name) : ID(nextID++), name(new wstring(name))
{
}

// 소멸자
Skill::~Skill()
{
	if (name != nullptr)
	{
		delete name;
		name = nullptr;
	}
}
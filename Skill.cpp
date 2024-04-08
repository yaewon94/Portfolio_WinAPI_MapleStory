#include "PCH.h"
#include "Skill.h"

// static 필드 초기화
UINT Skill::nextID = 0;


// 생성자
Skill::Skill(const wstring& name, SKILL_CALLBACK callback) 
	: ID(nextID++), name(name), callback(callback)
{
}

// 소멸자
Skill::~Skill()
{
	callback = nullptr;
}
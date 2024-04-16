#include "PCH.h"
#include "ActiveSkill.h"

// static 필드 초기화
Player* ActiveSkill::player = nullptr;

// 생성자
ActiveSkill::ActiveSkill(const wstring& name, int Cost)
	: Skill(name), Cost(Cost)
{
}

// 소멸자
ActiveSkill::~ActiveSkill()
{
}
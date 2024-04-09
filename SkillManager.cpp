#include "PCH.h"
#include "SkillManager.h"
#include "AttackActiveSkill.h"

// 생성자
SkillManager::SkillManager()
{
}

// 소멸자
SkillManager::~SkillManager()
{
	for (auto& skill : skills)
	{
		if (skill != nullptr)
		{
			delete skill;
			skill = nullptr;
		}
	}
}

// 초기화
void SkillManager::Init()
{
	ActiveSkill* activeSkill = nullptr;

	skills.push_back(new AttackActiveSkill(L"기본공격", Vec2::Right() * 200.f));
}

/*
// 공격스킬 발동
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
#include "PCH.h"
#include "SkillManager.h"
#include "AttackSkill.h"

// 생성자
SkillManager::SkillManager()
{
}

// 소멸자
SkillManager::~SkillManager()
{
	for (auto& pair : skillKeyMap)
	{
		if (pair.second != nullptr)
		{
			pair.second = nullptr;
		}
	}

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

	skills.push_back(new AttackActiveSkill(L"기본공격", KEY_CODE::SHIFT, Vec2::Right() * 200.f));
	activeSkill = (ActiveSkill*)skills.back();
	skillKeyMap.insert(make_pair(activeSkill->keyCode, activeSkill));
}

/*
// 공격스킬 발동
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
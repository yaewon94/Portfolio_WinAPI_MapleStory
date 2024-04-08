#include "PCH.h"
#include "SkillManager.h"
#include "Skill.h"

// 생성자
SkillManager::SkillManager()
{
}

// 소멸자
SkillManager::~SkillManager()
{
	for (Skill* skill : skills)
	{
		if (skill != nullptr)
		{
			//skill->callback = nullptr;
			delete skill;
			skill = nullptr;
		}
	}
}

// 초기화
void SkillManager::Init()
{
	skills.push_back(new Skill(L"기본공격", &SkillManager::ExecuteAttackSkill));
}

// 공격스킬 발동
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
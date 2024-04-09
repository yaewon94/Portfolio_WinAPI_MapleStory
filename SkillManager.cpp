#include "PCH.h"
#include "SkillManager.h"
#include "AttackSkill.h"

// ������
SkillManager::SkillManager()
{
}

// �Ҹ���
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

// �ʱ�ȭ
void SkillManager::Init()
{
	ActiveSkill* activeSkill = nullptr;

	skills.push_back(new AttackActiveSkill(L"�⺻����", KEY_CODE::SHIFT, Vec2::Right() * 200.f));
	activeSkill = (ActiveSkill*)skills.back();
	skillKeyMap.insert(make_pair(activeSkill->keyCode, activeSkill));
}

/*
// ���ݽ�ų �ߵ�
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
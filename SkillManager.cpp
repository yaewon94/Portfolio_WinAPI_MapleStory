#include "PCH.h"
#include "SkillManager.h"
#include "AttackActiveSkill.h"

// ������
SkillManager::SkillManager()
{
}

// �Ҹ���
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

// �ʱ�ȭ
void SkillManager::Init()
{
	ActiveSkill* activeSkill = nullptr;

	skills.push_back(new AttackActiveSkill(L"�⺻����", Vec2::Right() * 200.f));
}

/*
// ���ݽ�ų �ߵ�
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
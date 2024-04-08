#include "PCH.h"
#include "SkillManager.h"
#include "Skill.h"

// ������
SkillManager::SkillManager()
{
}

// �Ҹ���
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

// �ʱ�ȭ
void SkillManager::Init()
{
	skills.push_back(new Skill(L"�⺻����", &SkillManager::ExecuteAttackSkill));
}

// ���ݽ�ų �ߵ�
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
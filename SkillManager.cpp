#include "PCH.h"
#include "SkillManager.h"
#include "AttackActiveSkill.h"
#include "SkillObject.h"
#include "TimeManager.h"

// ������
SkillManager::SkillManager()
{
}

// �Ҹ���
SkillManager::~SkillManager()
{
	for (auto& skill : reservedSkills)
	{
		skill = nullptr;
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
	skills.push_back(new AttackActiveSkill(L"�⺻����", Vec2::Right() * 300));
}

// �� �����Ӹ��� ȣ��
void SkillManager::Tick()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	auto iter = reservedSkills.begin();

	// ����� ��ų �ð� üũ
	for (; iter!=reservedSkills.end(); )
	{
		auto skill = *iter;

		if (skill->time < skill->Delay)
		{
			skill->time += deltaTime;
			++iter;
		}
		else
		{
			skill->time = 0.f;
			skill->skillObject->SetActive(true);
			iter = reservedSkills.erase(iter);
		}
	}
}

/*
// ���ݽ�ų �ߵ�
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
#include "PCH.h"
#include "SkillManager.h"
#include "AttackActiveSkill.h"
#include "SkillObject.h"
#include "TimeManager.h"

// 생성자
SkillManager::SkillManager()
{
}

// 소멸자
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

// 초기화
void SkillManager::Init()
{
	skills.push_back(new AttackActiveSkill(L"기본공격", Vec2::Right() * 300));
}

// 매 프레임마다 호출
void SkillManager::Tick()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	auto iter = reservedSkills.begin();

	// 예약된 스킬 시간 체크
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
// 공격스킬 발동
void SkillManager::ExecuteAttackSkill(Skill& skill)
{
}
*/
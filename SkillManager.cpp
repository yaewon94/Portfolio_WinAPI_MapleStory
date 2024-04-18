#include "PCH.h"
#include "SkillManager.h"
#include "ActiveEtcSkill.h"
#include "AttackActiveSkill.h"
#include "LevelManager.h"
#include "MapManager.h"
#include "Player.h"
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
	skills.push_back(new AttackActiveSkill(L"기본공격", Vec2<float>::Right() * 300.f, 1.f));
	skills.push_back(new ActiveEtcSkill(L"달빛게이지", 20, &SkillManager::UseMoonlightGauge_Phase1));
}

// 매 프레임마다 호출
void SkillManager::Tick()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	auto iter = reservedSkills.begin();

	// 예약된 스킬 시간 체크
	for (; iter != reservedSkills.end(); )
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

// ========== 스킬 콜백함수 모음 ==========
// 윌 1페이즈 달빛게이지 스킬 사용
void SkillManager::UseMoonlightGauge_Phase1(ActiveSkill* skill)
{
	// 야매코드
	// mapIndex : 파란공간(0), 보라공간(1)
	static int mapIndex = 1;

	Player* player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	player->ChangeMap(MapManager::GetInstance().GetMap(mapIndex));

	if (mapIndex == 1) mapIndex = 0;
	else mapIndex = 1;
}
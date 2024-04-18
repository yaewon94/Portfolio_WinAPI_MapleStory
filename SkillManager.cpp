#include "PCH.h"
#include "SkillManager.h"
#include "ActiveEtcSkill.h"
#include "AttackActiveSkill.h"
#include "LevelManager.h"
#include "MapManager.h"
#include "Player.h"
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
	skills.push_back(new AttackActiveSkill(L"�⺻����", Vec2<float>::Right() * 300.f, 1.f));
	skills.push_back(new ActiveEtcSkill(L"�޺�������", 20, &SkillManager::UseMoonlightGauge_Phase1));
}

// �� �����Ӹ��� ȣ��
void SkillManager::Tick()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	auto iter = reservedSkills.begin();

	// ����� ��ų �ð� üũ
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

// ========== ��ų �ݹ��Լ� ���� ==========
// �� 1������ �޺������� ��ų ���
void SkillManager::UseMoonlightGauge_Phase1(ActiveSkill* skill)
{
	// �߸��ڵ�
	// mapIndex : �Ķ�����(0), �������(1)
	static int mapIndex = 1;

	Player* player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	player->ChangeMap(MapManager::GetInstance().GetMap(mapIndex));

	if (mapIndex == 1) mapIndex = 0;
	else mapIndex = 1;
}
#include "PCH.h"
#include "SkillManager.h"
#include "Animation.h"
#include "Animator.h"
#include "AssetManager.h"
#include "EnemyAttackSkill.h"
#include "LevelManager.h"
#include "MapManager.h"
#include "Player.h"
#include "PlayerAttackSkill.h"
#include "PlayerEtcSkill.h"
#include "SkillObject.h"
#include "TimeManager.h"

// ���
#define NO_LIMIT_DURATION (float)INT_MAX

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
	map<OBJECT_STATE, Animation*> animMap;

	skills.push_back(new PlayerAttackSkill(L"ü�ζ���Ʈ��", 1.f, DEFAULT_ANIM_DURATION*2.f, NO_LIMIT_DURATION, Vec2<float>::Right()*300.f, 3.f));
	animMap.insert(make_pair(OBJECT_STATE::DEFAULT, new Animation(nullptr, AssetManager::GetInstance().LoadTexture(L"ü�ζ���Ʈ��", L"Skill_ChainLightening.png"), 9)));
	skills.back()->animMap = animMap;
	skills.back()->index = 0;
	skills.push_back(new PlayerEtcSkill(L"�޺�������", 20, &SkillManager::UseMoonlightGauge_Phase1));
	skills.back()->index = 1;
	skills.push_back(new EnemyAttackSkill(L"�� �ٰŸ�����", 0.2f, DEFAULT_ANIM_DURATION*12, DEFAULT_ANIM_DURATION*3, Vec2<float>::Right() * 200.f, 5.f));
	skills.back()->SetObjectState(OBJECT_STATE::BOSSWILL_ATTACK_MELEE);
	skills.back()->index = 2;
}

// �� �����Ӹ��� ȣ��
void SkillManager::Tick()
{
	float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	auto iter = reservedSkills.begin();

	// ����� ��ų �ð� üũ
	for (; iter != reservedSkills.end(); )
	{
		auto skill = iter->first;
		auto skillObj = iter->second;

		if (skill->time < skill->Delay)
		{
			skill->time += deltaTime;
			++iter;
		}
		else
		{
			skill->time = 0.f;
			skillObj->SetActive(true);
			iter = reservedSkills.erase(iter);
		}
	}
}

// ========== ��ų �ݹ��Լ� ���� ==========
// �� 1������ �޺������� ��ų ���
void SkillManager::UseMoonlightGauge_Phase1()
{
	// �߸��ڵ�
	// mapIndex : �Ķ�����(0), �������(1)
	static int mapIndex = 1;

	Player* player = (Player*)LevelManager::GetInstance().FindObject(LAYER_TYPE::PLAYER);
	player->ChangeMap(MapManager::GetInstance().GetMap(mapIndex));

	if (mapIndex == 1) mapIndex = 0;
	else mapIndex = 1;
}
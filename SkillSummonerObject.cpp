#include "PCH.h"
#include "SkillSummonerObject.h"
#include "EnemyAttackSkill.h"
#include "SkillManager.h"
#include "SkillObject.h"

// 생성자
SkillSummonerObject::SkillSummonerObject(const wstring& name, LAYER_TYPE layer, int objCount, EnemyAttackSkill& skill) 
	: GameObject(name, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, layer)
	, ObjCount(objCount), skill(&skill)
{
	skillVelocityVec.resize(ObjCount);
}

// 복사 생성자
SkillSummonerObject::SkillSummonerObject(const SkillSummonerObject& origin) 
	: GameObject(origin)
	, ObjCount(origin.ObjCount)
	, skill(origin.skill), skillVelocityVec(origin.skillVelocityVec)
	, skillObjOffset(origin.skillObjOffset)
{
	// vector<SkillObject*> 는 Init() 에서 초기화
}

// 소멸자
SkillSummonerObject::~SkillSummonerObject()
{
	for (auto obj : skillObjects)
	{
		// 레벨에서 오브젝트 삭제될 때 자식오브젝트(스킬오브젝트들) 전부 삭제됨
		obj = nullptr;
	}

	skill = nullptr;
}

// 초기화
void SkillSummonerObject::Init()
{
	// 사용할 스킬 오브젝트 추가
	for (int i = 0; i < ObjCount; ++i)
	{
		skillObjects.push_back(new SkillObject(name, *this, skillObjOffset, DEFAULT_OBJECT_SCALE, LAYER_TYPE::ENEMY_SKILL));
		auto obj = skillObjects.back();
		obj->SetParent(*this);
		obj->AddSkill(skill->GetIndex());

		if (skillVelocityVec[i] != Vec2(0.f, 0.f))obj->SetSkill(skill, skill, skillVelocityVec[i]);
		else obj->SetSkill(skill, skill);
	}

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 스킬 소환(사용)
void SkillSummonerObject::UseSkill()
{
	GameObject::SetActive(true);

	for (auto skillObj : skillObjects)
	{
		// 딜레이 시간 이후에 스킬오브젝트 활성화 되도록 예약
		SkillManager::GetInstance().LaunchSkill(skill, skillObj);
	}
}
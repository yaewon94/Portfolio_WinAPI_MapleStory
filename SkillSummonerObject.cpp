#include "PCH.h"
#include "SkillSummonerObject.h"
#include "EnemyAttackSkill.h"
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
	, ObjCount(origin.ObjCount), skill(origin.skill), skillVelocityVec(origin.skillVelocityVec)
{
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
	for (int i=0; i<skillVelocityVec.size(); ++i)
	{
		skillObjects.push_back(new SkillObject(name, *this, DEFAULT_OBJECT_POS, DEFAULT_OBJECT_SCALE, LAYER_TYPE::ENEMY_SKILL));
		auto obj = skillObjects.back();
		obj->SetParent(*this);
		obj->AddSkill(skill->GetIndex());
		obj->SetSkill(skill, skill, skillVelocityVec[i]);
	}

	// 최상위 부모 Init() 호출
	GameObject::Init();
}

// 오브젝트 활성화,비활성화
void SkillSummonerObject::SetActive(bool flag)
{
	GameObject::SetActive(flag);

	if (flag)
	{
		// 스킬오브젝트 활성화
		for (auto skillObj : skillObjects)
		{
			skillObj->SetActive(true);
		}
	}
}
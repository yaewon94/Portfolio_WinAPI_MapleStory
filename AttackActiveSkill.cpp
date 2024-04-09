#include "PCH.h"
#include "AttackActiveSkill.h"
#include "LevelManager.h"
#include "SkillObject.h"

// static 필드 초기화
SkillObject* AttackActiveSkill::skillObject = nullptr;

// 생성자
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed)
{
}

// 소멸자
AttackActiveSkill::~AttackActiveSkill()
{
}

// 키 눌렸을 때 호출
void AttackActiveSkill::OnKeyPressed(KEY_CODE keyCode)
{
	if (skillObject->IsActive()) return;

	skillObject->SetSkill(*this);
	skillObject->SetActive(true);
}
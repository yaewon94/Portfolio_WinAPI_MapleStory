#include "PCH.h"
#include "AttackActiveSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "SkillObject.h"

// 생성자
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2<float> maxRange, float speed) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed), skillObject(nullptr)
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

	skillObject->GetParent()->GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	skillObject->SetSkill(*this);

	// 딜레이 시간 이후, 스킬 오브젝트 활성화
	SkillManager::GetInstance().LaunchSkill(*this);
}
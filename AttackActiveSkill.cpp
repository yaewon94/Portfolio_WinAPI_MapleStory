#include "PCH.h"
#include "AttackActiveSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// 생성자
AttackActiveSkill::AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed, bool canWithJump) 
	: ActiveSkill(name), maxRange(maxRange), speed(speed), canWithJump(canWithJump)
	, skillObject(nullptr)
{
}

// 소멸자
AttackActiveSkill::~AttackActiveSkill()
{
}

// 키 눌렸을 때 호출
void AttackActiveSkill::OnKeyPressed(KEY_CODE keyCode)
{
	// 발동 조건 체크
	if (skillObject->IsActive()) return;
	if (!canWithJump && !GetPlayer().CanJump()) return;

	// 상태 변경, 스킬 오브젝트에 현재 스킬 세팅
	GetPlayer().GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	skillObject->SetSkill(*this);

	// 딜레이 시간 이후, 스킬 오브젝트 활성화
	SkillManager::GetInstance().LaunchSkill(*this);
}
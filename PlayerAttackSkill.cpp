#include "PCH.h"
#include "PlayerAttackSkill.h"
#include "SkillManager.h"
#include "FSM.h"
#include "LevelManager.h"
#include "Player.h"
#include "SkillObject.h"

// 생성자
PlayerAttackSkill::PlayerAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed, int Cost) 
	: ActiveSkill(name, Cost)
	, AttackSkillModule(Coefficient, Delay, Duration, MaxRange, Speed)
{
}

// 소멸자
PlayerAttackSkill::~PlayerAttackSkill()
{
}

// 키 눌렸을 때 호출
void PlayerAttackSkill::OnKeyPressed(KEY_CODE keyCode)
{
	// 발동 조건 체크
	if (GetSkillObject().IsActive()) return;
	if (!canWithJump && !GetPlayer().CanJump()) return;

	// 상태 변경, 스킬 오브젝트에 현재 스킬 세팅
	GetPlayer().GetComponent<FSM>()->ChangeState(OBJECT_STATE::ATTACK);
	GetSkillObject().SetSkill(*this);

	// 딜레이 시간 이후, 스킬 오브젝트 활성화
	SkillManager::GetInstance().LaunchSkill(*this);
}
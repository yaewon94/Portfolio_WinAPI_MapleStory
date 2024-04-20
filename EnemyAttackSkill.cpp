#include "PCH.h"
#include "EnemyAttackSkill.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"
#include "SkillManager.h"
#include "SkillObject.h"

// 생성자
EnemyAttackSkill::EnemyAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed)
	: Skill(name)
	, AttackSkillModule(Coefficient, Delay, Duration, MaxRange, Speed)
{
}

// 소멸자
EnemyAttackSkill::~EnemyAttackSkill()
{
}

// 스킬 사용
void EnemyAttackSkill::UseSkill(GameObject* caster, SkillObject* skillObj)
{
	auto state = caster->GetComponent<FSM>()->GetCurrentState();

	// 발동조건 체크
	if (caster->GetComponent<FSM>()->GetCurrentState() == OBJECT_STATE::ATTACK)
	{
		// TODO : 플레이어 스킬클래스도 static Player* 대신 Skill::caster 필드 이용
		// 애니메이션 변경, 스킬 오브젝트에 현재 스킬 세팅
		caster->GetComponent<Animator>()->ChangeAnimation(GetObjectState());
		skillObj->SetSkill(*this);

		// 딜레이 시간 이후에 스킬오브젝트 활성화 되도록 예약
		SkillManager::GetInstance().LaunchSkill(this, skillObj);
	}
}
#include "PCH.h"
#include "EnemyAttackSkill.h"
#include "Animator.h"
#include "FSM.h"
#include "GameObject.h"
#include "SkillManager.h"
#include "SkillObject.h"

// ������
EnemyAttackSkill::EnemyAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed)
	: Skill(name)
	, AttackSkillModule(Coefficient, Delay, Duration, MaxRange, Speed)
{
}

// �Ҹ���
EnemyAttackSkill::~EnemyAttackSkill()
{
}

// ��ų ���
void EnemyAttackSkill::UseSkill(GameObject* caster, SkillObject* skillObj)
{
	auto state = caster->GetComponent<FSM>()->GetCurrentState();

	// �ߵ����� üũ
	if (caster->GetComponent<FSM>()->GetCurrentState() == OBJECT_STATE::ATTACK)
	{
		// TODO : �÷��̾� ��ųŬ������ static Player* ��� Skill::caster �ʵ� �̿�
		// �ִϸ��̼� ����, ��ų ������Ʈ�� ���� ��ų ����
		caster->GetComponent<Animator>()->ChangeAnimation(GetObjectState());
		skillObj->SetSkill(*this);

		// ������ �ð� ���Ŀ� ��ų������Ʈ Ȱ��ȭ �ǵ��� ����
		SkillManager::GetInstance().LaunchSkill(this, skillObj);
	}
}
#include "PCH.h"
#include "EnemyAttackSkill.h"
#include "Animator.h"
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
void EnemyAttackSkill::UseSkill()
{
	// �ߵ����� üũ
	if (GetSkillObject().IsActive()) return;

	// TODO : �÷��̾� ��ųŬ������ static Player* ��� Skill::caster �ʵ� �̿�
	// �ִϸ��̼� ����, ��ų ������Ʈ�� ���� ��ų ����
	GetCaster().GetComponent<Animator>()->ChangeAnimation(GetObjectState());
	GetSkillObject().SetSkill(*this);

	// ������ �ð� ���Ŀ� ��ų������Ʈ Ȱ��ȭ �ǵ��� ����
	SkillManager::GetInstance().LaunchSkill(*this);
}
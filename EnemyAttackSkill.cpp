#include "PCH.h"
#include "EnemyAttackSkill.h"

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
#include "PCH.h"
#include "EnemyAttackSkill.h"

// 持失切
EnemyAttackSkill::EnemyAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed)
	: Skill(name)
	, AttackSkillModule(Coefficient, Delay, Duration, MaxRange, Speed)
{
}

// 社瑚切
EnemyAttackSkill::~EnemyAttackSkill()
{
}
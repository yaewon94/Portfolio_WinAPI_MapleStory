#pragma once
#include "Skill.h"
#include "AttackSkillModule.h"

// 몬스터 또는 레벨자체 공격스킬 클래스
class EnemyAttackSkill final : public Skill, public AttackSkillModule
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(EnemyAttackSkill);

private:
	EnemyAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed);
	~EnemyAttackSkill();

public:
	virtual void UseSkill() override;
};
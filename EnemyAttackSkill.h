#pragma once
#include "Skill.h"
#include "AttackSkillModule.h"

// ���� �Ǵ� ������ü ���ݽ�ų Ŭ����
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
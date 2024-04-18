#pragma once
#include "ActiveSkill.h"
#include "AttackSkillModule.h"

class SkillObject;

// 공격형 스킬 (액티브)
class PlayerAttackSkill final : public ActiveSkill, public AttackSkillModule
{
	friend class SkillManager;
	NO_CSTR_COPY_ASSIGN(PlayerAttackSkill);

private:
	bool canWithJump = false;		// 점프 공격 가능 여부

private:
	PlayerAttackSkill(const wstring& name, float Coefficient, float Delay, float Duration, Vec2<float> MaxRange, float Speed, int Cost=0);
	~PlayerAttackSkill();

public:
	virtual void OnKeyPressed(KEY_CODE keyCode) override;
};
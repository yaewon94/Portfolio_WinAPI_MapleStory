#pragma once
#include "ActiveSkill.h"

class SkillObject;

// 공격형 스킬 (액티브)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	Vec2 maxRange;	// 최대 이동범위 (넘어서면 자동으로 비활성화됨)

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, KEY_CODE keyCode, Vec2 maxRange);
	~AttackActiveSkill();

public:
	virtual void OnKeyPressed(KEY_CODE keyCode) override {}
	virtual void OnKeyDown(KEY_CODE keyCode) override {}
};
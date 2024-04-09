#pragma once
#include "Skill.h"
#include "IKeyEvent.h"

// 플레이어가 직접 키를 눌러서 발동하는 스킬의 상위클래스
// [abstract class]
class ActiveSkill : public Skill, public IKeyEvent
{
	NO_CSTR_COPY_ASSIGN(ActiveSkill);

	friend class SkillManager;

private:
	virtual void Init() override final {}
	virtual void Tick() override final {}
	virtual void FinalTick() override final {}

protected:
	ActiveSkill(const wstring& name);
	~ActiveSkill();
};
#pragma once
#include "Skill.h"
#include "IKeyEvent.h"

// 플레이어가 직접 키를 눌러서 발동하는 스킬의 상위클래스
// [abstract class]
class ActiveSkill : public Skill, public IKeyEvent
{
	NO_CSTR_COPY_ASSIGN(ActiveSkill);

	friend class SkillManager;

protected:
	ActiveSkill(const wstring& name);
	~ActiveSkill();

	virtual void OnKeyPressed(KEY_CODE) override {};
	virtual void OnKeyDown(KEY_CODE) override {};
	virtual void OnKeyReleased(KEY_CODE) override {};
};
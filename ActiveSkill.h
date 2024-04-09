#pragma once
#include "Skill.h"
#include "IKeyEvent.h"

// �÷��̾ ���� Ű�� ������ �ߵ��ϴ� ��ų�� ����Ŭ����
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
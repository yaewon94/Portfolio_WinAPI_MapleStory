#pragma once
#include "ActiveSkill.h"

class SkillObject;

// ������ ��ų (��Ƽ��)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	Vec2 maxRange;	// �ִ� �̵����� (�Ѿ�� �ڵ����� ��Ȱ��ȭ��)

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, KEY_CODE keyCode, Vec2 maxRange);
	~AttackActiveSkill();

public:
	virtual void OnKeyPressed(KEY_CODE keyCode) override {}
	virtual void OnKeyDown(KEY_CODE keyCode) override {}
};
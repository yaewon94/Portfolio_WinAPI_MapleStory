#pragma once
#include "ActiveSkill.h"

class SkillObject;

// ������ ��ų (��Ƽ��)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	static SkillObject* skillObject;	// [CHECK] �ٸ� ��ų�� �߰��Ǹ� static�� �ƴ϶� �ν��Ͻ� �ʵ�� �ٲ�� �Ҽ���

public:
	static void SetSkillObject(SkillObject& skillObject);

private:
	const Vec2 maxRange;	// �ִ� �̵����� (�Ѿ�� �ڵ����� ��Ȱ��ȭ��)
	const float speed;

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, Vec2 maxRange, float speed=2.f);
	~AttackActiveSkill();

public:
	Vec2 GetMaxRange() const { return maxRange; }
	float GetSpeed() const { return speed; }

	virtual void OnKeyPressed(KEY_CODE keyCode) override;
	virtual void OnKeyDown(KEY_CODE keyCode) override {}
};

// ��ų ������Ʈ ����
inline void AttackActiveSkill::SetSkillObject(SkillObject& obj)
{
	if (skillObject == nullptr) skillObject = &obj;
}
#pragma once
#include "ActiveSkill.h"

class SkillObject;

// ������ ��ų (��Ƽ��)
class AttackActiveSkill final : public ActiveSkill
{
	friend class SkillManager;

private:
	SkillObject* skillObject;

	const float Coefficient;	// ������ ���

	Vec2<float> maxRange;	// �ִ� �̵����� (�Ѿ�� �ڵ����� ��Ȱ��ȭ��)
	float speed;		// ��ų ������Ʈ �̵� �ӵ�

	const float Delay = DEFAULT_ANIM_DURATION * 2;	// Ű �Է� ��, ��ų ������Ʈ�� Ȱ��ȭ �Ǳ���� �ɸ��� �ð�
	float time = 0.f;		// ��ų ���� �� ����ð�

	bool canWithJump;		// ���� ���� ���� ����

	NO_CSTR_COPY_ASSIGN(AttackActiveSkill);
	AttackActiveSkill(const wstring& name, Vec2<float> maxRange, float Coefficient, float speed=2.f, bool canWithJump=false);
	~AttackActiveSkill();

public:
	float GetCoefficient() { return Coefficient; }
	Vec2<float> GetMaxRange() const { return maxRange; }
	float GetSpeed() const { return speed; }
	void SetSkillObject(SkillObject& skillObject);

	virtual void OnKeyPressed(KEY_CODE keyCode) override;
};

// ��ų ������Ʈ ����
inline void AttackActiveSkill::SetSkillObject(SkillObject& obj)
{
	if (skillObject == nullptr) skillObject = &obj;
}
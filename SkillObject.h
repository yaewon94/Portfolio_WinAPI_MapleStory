#pragma once
#include "GameObject.h"

class AttackSkillModule;

// ��ų������Ʈ Ŭ����
class SkillObject : public GameObject
{
private:
	GameObject& caster;			// ��ų ������
	const Vec2<float> Offset;	// ������ ���� ������
	Vec2<float> startPos;		// ��ų Ȱ��ȭ �Ǿ��� �� ������ǥ (��ų ������ ��ǥ + Offset)

	AttackSkillModule* skill;
	float time = 0.f;	// ��ų������Ʈ Ȱ��ȭ ���� ����ð�

public:
	SkillObject(const wstring& name, GameObject& caster, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer);
	SkillObject(const SkillObject& origin);
	~SkillObject();
	virtual SkillObject* Clone() override { return new SkillObject(*this); }

	virtual void Init() override;
	virtual void Tick() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override {}
	virtual void OnCollisionExit(GameObject& other) override {}

	void SetSkill(AttackSkillModule& skill) { this->skill = &skill; }
	AttackSkillModule* GetSkill() { return skill; }

	virtual void SetActive(bool flag) override;
};
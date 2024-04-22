#pragma once
#include "GameObject.h"

class Animation;
class AttackSkillModule;
class Skill;

// ��ų������Ʈ Ŭ����
class SkillObject : public GameObject
{
private:
	GameObject& caster;			// ��ų ������
	const Vec2<float> Offset;	// ������ ���� ������
	Vec2<float> velocity;		// ��ų �̵��ӵ� (, �ִ� �̵��Ÿ�)
	Vec2<float> startPos;		// ��ų Ȱ��ȭ �Ǿ��� �� ������ǥ (��ų ������ ��ǥ + Offset)

	// ERROR : ���迡��
	// �ΰ� �θ� �޶� ����� ��ȯ�Ҽ��� ����
	AttackSkillModule* attackSkillPtr;	// ���� ��ų�� ���� ������
	Skill* skillPtr;					// ���� ��ų�� ���� ������

	float time = 0.f;	// ��ų������Ʈ Ȱ��ȭ ���� ����ð�

	// ��� ��ų ����
	map<int, map<OBJECT_STATE, Animation*>> skillMap;	// key:��ų�ε���, value:����-�ִϸ��̼�

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

	void AddSkill(int index);
	AttackSkillModule* GetSkill() { return attackSkillPtr; }

	// ERROR : ��ųŬ���� ���� �߸������
	// AttackSkillModule�̶� Skill�̶� ������ �ٸ� Ŭ������ ����ȯ�� �ȉ�. �� ������ Ÿ������ �� �޾ƾ� ��
	void SetSkill(AttackSkillModule* me_attack, Skill* me_skill);
	void SetSkill(AttackSkillModule* me_attack, Skill* me_skill, Vec2<float> velocity);

	virtual void SetActive(bool flag) override;
};
#pragma once
#include "GameObject.h"

class AttackSkillModule;

// 스킬오브젝트 클래스
class SkillObject : public GameObject
{
private:
	const Vec2<float> StartPos = offset;
	AttackSkillModule* skill;

public:
	SkillObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer);
	SkillObject(const SkillObject& origin);
	~SkillObject();
	virtual SkillObject* Clone() override { return new SkillObject(*this); }

	virtual void Init() override;
	virtual void Tick() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override {}
	virtual void OnCollisionExit(GameObject& other) override {}

	virtual void SetActive(bool flag) override;
	void SetSkill(AttackSkillModule& skill) { this->skill = &skill; }
	AttackSkillModule* GetSkill() { return skill; }
};

// 오브젝트 활성화 / 비활성화
inline void SkillObject::SetActive(bool flag)
{
	offset = StartPos;
	GameObject::SetActive(flag);
}
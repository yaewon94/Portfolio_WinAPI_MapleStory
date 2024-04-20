#pragma once
#include "GameObject.h"

class AttackSkillModule;

// 스킬오브젝트 클래스
class SkillObject : public GameObject
{
private:
	const Vec2<float> StartPos = offset;
	AttackSkillModule* skill;
	float time = 0.f;	// 스킬오브젝트 활성화 이후 경과시간

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

	void SetSkill(AttackSkillModule& skill) { this->skill = &skill; }
	AttackSkillModule* GetSkill() { return skill; }
};
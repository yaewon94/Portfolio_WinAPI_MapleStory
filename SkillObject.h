#pragma once
#include "GameObject.h"

class AttackSkillModule;

// 스킬오브젝트 클래스
class SkillObject : public GameObject
{
private:
	GameObject& caster;			// 스킬 시전자
	const Vec2<float> Offset;	// 시전자 기준 오프셋
	Vec2<float> startPos;		// 스킬 활성화 되었을 때 시작좌표 (스킬 시전자 좌표 + Offset)

	AttackSkillModule* skill;
	float time = 0.f;	// 스킬오브젝트 활성화 이후 경과시간

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
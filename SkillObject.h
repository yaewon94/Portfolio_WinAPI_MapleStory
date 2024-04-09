#pragma once
#include "GameObject.h"

class AttackActiveSkill;

// TODO : 스킬 추가하면 SkillObject 클래스 세분화 해야할듯
class SkillObject : public GameObject
{
private:
	static AttackActiveSkill* skill;	// [CHECK] 나중에 static말고 인스턴스 필드로 바꿀 수 있음

private:
	const Vec2 StartPos = offset;

public:
	SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer);
	SkillObject(const SkillObject& origin);
	~SkillObject();
	virtual SkillObject* Clone() override { return new SkillObject(*this); }

	virtual void Init() override;
	virtual void Tick() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override {}
	virtual void OnCollisionExit(GameObject& other) override {}

	virtual void SetActive(bool flag) override;
	void SetSkill(AttackActiveSkill& skill) { SkillObject::skill = &skill; }
};

// 오브젝트 활성화 / 비활성화
inline void SkillObject::SetActive(bool flag)
{
	offset = StartPos;
	GameObject::SetActive(flag);
}
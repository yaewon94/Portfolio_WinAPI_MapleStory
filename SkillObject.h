#pragma once
#include "GameObject.h"

class SkillObject : public GameObject
{
public:
	SkillObject(const wstring& name, Vec2 offset, Vec2 scale, LAYER_TYPE layer);
	SkillObject(const SkillObject& origin);
	~SkillObject();
	virtual SkillObject* Clone() override { return new SkillObject(*this); }

	virtual void OnCollisionEnter(GameObject& other) override {}
	virtual void OnCollisionStay(GameObject& other) override {}
	virtual void OnCollisionExit(GameObject& other) override {}
};
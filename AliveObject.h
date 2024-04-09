#pragma once
#include "GameObject.h"

class Skill;
class SkillObject;

// 이동, 점프, 스킬사용이 가능하고 생명주기가 있는 오브젝트의 상위 클래스
// [abstract class]
class AliveObject : public GameObject
{
private:
	vector<Skill*> skills;
	SkillObject* skillObject;

protected:
	Vec2 dir;
	float speed;
	float jumpPower;
	bool canJump = false;

	AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed=200.f, float jumpPower=700.f);
	AliveObject(const AliveObject& origin);
	~AliveObject();

	Skill& AddSkill(Skill& skill);
	void SetSkillObject(SkillObject& skillObject) { this->skillObject = &skillObject; }

	void Move();
	void Jump();

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};

// 사용 가능한 스킬 추가
inline Skill& AliveObject::AddSkill(Skill& skill)
{
	skills.push_back(&skill);
	return *skills.back();
}
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
	Vec2<float> dir = Vec2<float>::Left();
	Vec2<float> prevDir;
	float speed;
	bool canMove = true;

	float jumpPower;
	bool canJump = false;

	AliveObject(const wstring& name, Vec2<float> offset, Vec2<int> scale, LAYER_TYPE layer, float speed=200.f, float jumpPower=700.f);
	AliveObject(const AliveObject& origin);
	~AliveObject();

	Skill& AddSkill(Skill& skill);
	void SetSkillObject(SkillObject& skillObject) { this->skillObject = &skillObject; }

	void Move();
	void Jump();

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

public:
	Vec2<float> GetDirection() const { return dir; }
	bool CanJump() { return canJump; }
};

// 사용 가능한 스킬 추가
inline Skill& AliveObject::AddSkill(Skill& skill)
{
	skills.push_back(&skill);
	return *skills.back();
}
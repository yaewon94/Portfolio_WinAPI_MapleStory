#pragma once
#include "GameObject.h"

class Skill;
class SkillObject;
class Texture;

// 이동, 점프, 스킬사용이 가능하고 생명주기가 있는 오브젝트의 상위 클래스
// [abstract class]
class AliveObject : public GameObject
{
private:
	vector<Skill*> skills;
	SkillObject* skillObject;

	const int MaxHP;				// 최대체력
	int curHP = MaxHP;				// 현재체력
	Texture* HP_fillTex = nullptr;	// UI 체력바

	int power;			// 공격력

	Vec2<float> prevDir;	// 이전 이동방향
	float speed;			// 이동 스피드
	bool canMove = true;	// 이동 가능 여부

	float jumpPower;	// 점프력

protected:
	Vec2<float> dir = Vec2<float>::Left();	// 현재 이동방향
	bool canJump = false;	// 점프 가능 여부

	AliveObject(const wstring& name, LAYER_TYPE layer, int MaxHP, int power = 100, float speed = 200.f, float jumpPower = 500.f);
	AliveObject(const AliveObject& origin);
	~AliveObject();

	int GetCurrentHP() { return curHP; }
	Skill& GetSkill(int index) { assert(index < skills.size()); return *skills[index]; }

	void SetSkillObject(SkillObject& skillObject) { this->skillObject = &skillObject; }

	void Move();
	void Jump();

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

	void OnChangeHP(int changedHP);

public:
	int GetPower() { return power; }
	Vec2<float> GetDirection() const { return dir; }
	bool CanJump() { return canJump; }

	void SetHPbar(Texture& fill_texture) { HP_fillTex = &fill_texture; }

	Skill& AddSkill(Skill& skill);
};

// 사용 가능한 스킬 추가
inline Skill& AliveObject::AddSkill(Skill& skill)
{
	skills.push_back(&skill);
	return *skills.back();
}
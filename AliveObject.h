#pragma once
#include "GameObject.h"

struct Skill;

// �̵�, ����, ��ų����� �����ϰ� �����ֱⰡ �ִ� ������Ʈ�� ���� Ŭ����
class AliveObject : public GameObject
{
private:
	vector<Skill*> skills;

protected:
	Vec2 dir;
	float speed;
	float jumpPower;
	bool canJump = false;

	AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed=200.f, float jumpPower=700.f);
	AliveObject(const AliveObject& origin);
	~AliveObject();

	void AddSkill(Skill& skill);

	void Move();
	void Jump();

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};
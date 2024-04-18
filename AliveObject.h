#pragma once
#include "GameObject.h"

class Skill;
class SkillObject;
class Texture;

// �̵�, ����, ��ų����� �����ϰ� �����ֱⰡ �ִ� ������Ʈ�� ���� Ŭ����
// [abstract class]
class AliveObject : public GameObject
{
private:
	vector<Skill*> skills;
	SkillObject* skillObject;

	const int MaxHP;				// �ִ�ü��
	int curHP = MaxHP;				// ����ü��
	Texture* HP_fillTex = nullptr;	// UI ü�¹�

	int power;			// ���ݷ�

	Vec2<float> prevDir;	// ���� �̵�����
	float speed;			// �̵� ���ǵ�
	bool canMove = true;	// �̵� ���� ����

	float jumpPower;	// ������

protected:
	Vec2<float> dir = Vec2<float>::Left();	// ���� �̵�����
	bool canJump = false;	// ���� ���� ����

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

// ��� ������ ��ų �߰�
inline Skill& AliveObject::AddSkill(Skill& skill)
{
	skills.push_back(&skill);
	return *skills.back();
}
#pragma once
#include "GameObject.h"

// �̵�, ����, ��ų����� �����ϰ� �����ֱⰡ �ִ� ������Ʈ�� ���� Ŭ����
class AliveObject : public GameObject
{
protected:
	Vec2 dir;
	float speed;
	float jumpPower;
	bool canJump = false;

	AliveObject(const wstring& name, Vec2 pos, Vec2 scale, LAYER_TYPE layer, float speed=200.f, float jumpPower=700.f);
	AliveObject(const AliveObject& origin);
	~AliveObject();

	virtual void Move() = 0;
	virtual void Jump() = 0;
};
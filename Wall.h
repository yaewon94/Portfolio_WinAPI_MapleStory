#pragma once
#include "GameObject.h"

// �� ������Ʈ
// Background, Ground, Wall Ŭ���� �и��� �ʿ� �����µ�, �ð������� �̹��� �׳� ����
class Wall final : public GameObject
{
public:
	Wall(Vec2<float> pos, Vec2<int> scale);
	Wall(const Wall& origin);
	~Wall();
	virtual Wall* Clone() override { return new Wall(*this); }

	virtual void Init() override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;
};
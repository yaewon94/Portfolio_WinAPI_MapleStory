#pragma once
#include "GameObject.h"
#include "IKeyEvent.h"
#include "IMovable.h"
#include "IJumpable.h"

class Player final : public GameObject, public IKeyEvent, IMovable, IJumpable
{
private:
	bool canJump = false;

public:
	Player(const wstring& name, Vec2 pos, Vec2 scale);
	Player(const Player& origin);
	~Player();
	virtual Player* Clone() override { return new Player(*this); }

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;

	virtual void OnCollisionEnter(GameObject& other) override;
	virtual void OnCollisionStay(GameObject& other) override;
	virtual void OnCollisionExit(GameObject& other) override;

private:
	virtual void Move() override;
	virtual void Jump() override;
};
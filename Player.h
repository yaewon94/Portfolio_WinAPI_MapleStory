#pragma once
#include "Component.h"
#include "IKeyEvent.h"
#include "IMovable.h"

class Player final : public Component, public IKeyEvent, IMovable
{
public:
	Player(GameObject* owner);
	Player(const Player& origin);
	~Player();

	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;

	virtual Player* Clone() override { return new Player(*this); }

private:
	virtual void Move() override;
};
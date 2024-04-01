#pragma once
#include "Component.h"
#include "IKeyEvent.h"
#include "IMovable.h"

class Player final : public Component, public IKeyEvent, IMovable
{
public:
	Player(GameObject& owner);
	Player(const Player& origin);
	Player(Player&& origin) noexcept;
	~Player();

	Player& operator=(const Player& origin);
	Player& operator=(Player&& origin) noexcept;
	virtual Player* Clone() override { return new Player(*this); }

	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;

private:
	virtual void Move() override;
};
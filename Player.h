#pragma once
#include "AliveObject.h"
#include "IKeyEvent.h"

class Player final : public AliveObject, public IKeyEvent
{
public:
	Player(const wstring& name, Vec2 pos, Vec2 scale);
	Player(const Player& origin);
	~Player();
	virtual Player* Clone() override { return new Player(*this); }

	virtual void Init() override;

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;
};
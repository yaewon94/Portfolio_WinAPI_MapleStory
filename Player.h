#pragma once
#include "GameObject.h"
#include "IMovable.h"
#include "IKeyEvent.h"

// 플레이어 클래스
class Player final : public GameObject, public IKeyEvent, IMovable
{
	// 이동 방향 enum
	enum class MOVE_DIRECTION : int
	{
		LEFT = -1, RIGHT = 1
	};

private:
	MOVE_DIRECTION move_direction;

public :
	Player(const wstring& name, Vec2 pos, Vec2 Scale);
	Player(const Player& origin);
	~Player();

	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}

	virtual void OnKeyPressed(KEY_CODE key) override;
	virtual void OnKeyDown(KEY_CODE key) override;

private:
	virtual void Move() override;
};
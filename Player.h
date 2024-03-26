#pragma once
#include "GameObject.h"

// 플레이어 클래스
class Player final : public GameObject
{
public :
	Player(const wstring& name, Vec2 pos, Vec2 Scale);
	Player(const Player& origin);
	~Player();

	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}
	virtual void Render() override {}
};
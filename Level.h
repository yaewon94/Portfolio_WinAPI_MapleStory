#pragma once
#include "Entity.h"

class GameObject;

// 게임 맵 구조 등을 설계하기 위한 클래스
// abstract class
class Level : public Entity
{
protected:
	vector<GameObject*> objects;

	Level(const wstring&);
	Level(const Level&) = delete;
	virtual ~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

private:
	friend class LevelManager;

	virtual void Init() override final;
	virtual void Tick() override final;
	virtual void FinalTick() override final;
	virtual void Render() override final;

	void DeleteObjects();
};
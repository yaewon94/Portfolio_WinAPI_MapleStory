#pragma once
#include "Entity.h"

class GameObject;

// 게임 맵 구조 등을 설계하기 위한 클래스
// abstract class
class Level : public Entity
{
	typedef vector<GameObject*> Layer;

private:
	array<Layer, (UINT)LAYER_TYPE::LAYER_TYPE_COUNT> objects;

protected:
	Level(const wstring&);
	Level(const Level&) = delete;
	virtual ~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(GameObject& object, LAYER_TYPE layer);
	GameObject& FindObject(LAYER_TYPE layer);

private:
	friend class LevelManager;

	virtual void Init() override final;
	virtual void Tick() override final;
	virtual void FinalTick() override final;
	virtual void Render() override final;

	void DeleteObjects();
};
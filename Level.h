#pragma once
#include "Entity.h"

class GameObject;

// ���� �� ���� ���� �����ϱ� ���� Ŭ����
// abstract class
class Level : public Entity
{
private:
	map<LAYER_TYPE, vector<GameObject*>> objectMap;

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
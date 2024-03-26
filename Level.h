#pragma once
#include "Entity.h"

class GameObject;

// ���� �� ���� ���� �����ϱ� ���� Ŭ����
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
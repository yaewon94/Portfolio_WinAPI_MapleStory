#pragma once
#include "Entity.h"

class GameObject;

// ���� �� ���� ���� �����ϱ� ���� Ŭ����
// abstract class
class Level : public Entity
{
	NO_COPY_CSTR(Level);

private:
	wstring name;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> objects; // ������ ���������� �迭�� ����

protected:
	Level(const wstring& name);
	virtual ~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	GameObject& AddObject(LAYER_TYPE layer, const wstring& name, Vec2 pos, Vec2 scale);

private:
	friend class LevelManager;

	virtual void Init() override final;
	virtual void Tick() override final;
	virtual void FinalTick() override final;
	void Render();

	GameObject* FindObject(LAYER_TYPE layer);
	void DeleteObjects();
};
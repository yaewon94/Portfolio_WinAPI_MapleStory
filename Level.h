#pragma once
#include "Entity.h"
#include "GameObject.h"

class Camera;

// 게임 맵 구조 등을 설계하기 위한 클래스
// abstract class
class Level : public Entity
{
	NO_CSTR_COPY_ASSIGN(Level);

private:
	wstring name;
	Camera* mainCamera;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> objects; // 렌더링 순서때문에 배열로 설정

protected:
	Level(const wstring& name);
	virtual ~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	template<typename T> requires std::derived_from<T, GameObject> GameObject* AddObject(T&& object);

private:
	friend class LevelManager;

	virtual void Init() override final;
	virtual void Tick() override final;
	virtual void FinalTick() override final;
	void Render();

	GameObject* FindObject(LAYER_TYPE layer);
	void DeleteObjects();
};

// 게임오브젝트 추가
template<typename T> requires std::derived_from<T, GameObject>
inline GameObject* Level::AddObject(T&& object)
{
	//size_t layer_idx = (size_t)layer;
	//assert(layer_idx < objects.max_size());

	T* clone = new T(std::move(object));
	objects[(size_t)clone->GetLayer()].push_back(clone);

	return clone;
}
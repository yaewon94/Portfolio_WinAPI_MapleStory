#pragma once
#include "Entity.h"
#include "GameObject.h"

class Camera;
class Map;

// 게임 맵 구조 등을 설계하기 위한 클래스
// abstract class
class Level : public Entity
{
	NO_CSTR_COPY_ASSIGN(Level);

	// ===== static 멤버 =====
private:
	static Camera* mainCamera;

public:
	static Camera& GetMainCamera() { return *mainCamera; }

	// ===== 인스턴스 멤버 =====
private:
	wstring name;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> objects; // 렌더링 순서때문에 배열로 설정

protected:
	Level(const wstring& name);
	~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void OnUseLevelSkill(int currentSkillCost) {}	// 현재 레벨에서만 쓸 수 있는 특수한 스킬을 사용했을 때 호출

	template<typename T> requires std::derived_from<T, GameObject> GameObject* AddObject(const T& object);

private:
	friend class LevelManager;

	void Init();
	void Tick();
	void FinalTick();
	void Render();

	GameObject* FindObject(LAYER_TYPE layer);
	void DeleteObjects();
};

// 게임오브젝트 추가
template<typename T> requires std::derived_from<T, GameObject>
inline GameObject* Level::AddObject(const T& object)
{
	T* clone = new T(object);
	objects[(size_t)clone->GetLayer()].push_back(clone);

	return clone;
}
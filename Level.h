#pragma once
#include "Entity.h"
#include "GameObject.h"

class Camera;
class Map;
class Player;

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
	Player* player;

protected:
	Level(const wstring& name);
	~Level();

	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

	virtual void Enter() = 0;	// 각 레벨의 오브젝트 초기화 구현
	virtual void Exit() = 0;	// 각 레벨의 오브젝트 선택적 삭제 구현

	Player& GetPlayer() { return *player; }
	void SetPlayer(Player* player) { this->player = player; }

	// TODO : 보스레이드 전용 레벨 클래스를 분리해서 선언해야 함
	virtual void OnAlertBossHpZero() {}
	virtual void OnChangeGaugePercent(int currentSkillCost) {}

	template<typename T> requires std::derived_from<T, GameObject> GameObject* AddObject(const T& object);

private:
	friend class LevelManager;

	void Render();

	GameObject* FindObject(LAYER_TYPE layer);
};

// 게임오브젝트 추가
template<typename T> requires std::derived_from<T, GameObject>
inline GameObject* Level::AddObject(const T& object)
{
	T* clone = new T(object);
	objects[(size_t)clone->GetLayer()].push_back(clone);

	return clone;
}
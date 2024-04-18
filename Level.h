#pragma once
#include "Entity.h"
#include "GameObject.h"

class Camera;
class Map;
class Player;

// ���� �� ���� ���� �����ϱ� ���� Ŭ����
// abstract class
class Level : public Entity
{
	NO_CSTR_COPY_ASSIGN(Level);

	// ===== static ��� =====
private:
	static Camera* mainCamera;

public:
	static Camera& GetMainCamera() { return *mainCamera; }

	// ===== �ν��Ͻ� ��� =====
private:
	wstring name;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> objects; // ������ ���������� �迭�� ����
	Player* player;

protected:
	Level(const wstring& name);
	~Level();

	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	Player& GetPlayer() { return *player; }
	void SetPlayer(Player* player) { this->player = player; }

	// TODO : �������̵� ���� ���� Ŭ������ �и��ؼ� �����ؾ� ��
	virtual void OnAlertBossHpZero() {}
	virtual void OnChangeGaugePercent(int currentSkillCost) {}

	template<typename T> requires std::derived_from<T, GameObject> GameObject* AddObject(const T& object);

private:
	friend class LevelManager;

	void Render();

	GameObject* FindObject(LAYER_TYPE layer);
	void DeleteObjects();
};

// ���ӿ�����Ʈ �߰�
template<typename T> requires std::derived_from<T, GameObject>
inline GameObject* Level::AddObject(const T& object)
{
	T* clone = new T(object);
	objects[(size_t)clone->GetLayer()].push_back(clone);

	return clone;
}
#pragma once
#include "Entity.h"
#include "GameObject.h"

class Camera;
class Map;

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

protected:
	Level(const wstring& name);
	~Level();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void OnUseLevelSkill(int currentSkillCost) {}	// ���� ���������� �� �� �ִ� Ư���� ��ų�� ������� �� ȣ��

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

// ���ӿ�����Ʈ �߰�
template<typename T> requires std::derived_from<T, GameObject>
inline GameObject* Level::AddObject(const T& object)
{
	T* clone = new T(object);
	objects[(size_t)clone->GetLayer()].push_back(clone);

	return clone;
}
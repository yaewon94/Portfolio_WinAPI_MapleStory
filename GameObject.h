#pragma once
#include "Entity.h"

class Camera;
class Component;

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class GameObject : public Entity
{
// ========== static ��� ==========
private:
	static Camera* mainCamera;

public:
	static void SetMainCamera(Camera* mainCamera) { GameObject::mainCamera = mainCamera; }

// ========== �ν��Ͻ� ��� ==========
private:
	vector<Component*> components;
	LAYER_TYPE layer;
	
protected:
	wstring name;
	Vec2 pos;
	Vec2 scale;

	GameObject(const wstring& name, Vec2 pos, Vec2 Scale, LAYER_TYPE layer);
	GameObject(const GameObject& origin);
	~GameObject();

public:
	void Destroy(){ if (this != nullptr) delete this; }
	virtual GameObject* Clone() = 0;

	Vec2 GetPos() const { return pos; }
	Vec2 GetScale() const { return scale; }
	LAYER_TYPE GetLayer() { return layer; }
	void SetPos(Vec2 pos) { this->pos = pos; }

	// [check] �ӽ�
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override;
	void Render();

	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();

	// [check] CollisionManager������ ȣ���� �� �ִ� ��� ���� friend class ����
	virtual void OnCollisionEnter(GameObject& other) = 0;
	virtual void OnCollisionStay(GameObject& other) = 0;
	virtual void OnCollisionExit(GameObject& other) = 0;
};

// ������Ʈ �߰�
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent()
{
	T* clone = nullptr;

	if (GetComponent<T>() != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, name + L"�� �̹� ������ �ִ� ������Ʈ �Դϴ� : " + ::to_wstring(typeid(T).name())); \
	}
	else
	{
		clone = new T(*this); 
		components.push_back(clone); 
	}
	return clone;
}

// ������Ʈ ��������
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::GetComponent()
{
	T* component = nullptr;

	for (auto item : components)
	{
		//if (typeid(item) == typeid(T*)) return (T*)item;
		component = dynamic_cast<T*>(item);
		if (component != nullptr) return component;
	}

	return component;
}

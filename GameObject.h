#pragma once
#include "Entity.h"

class Component;

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class GameObject final : public Entity
{
private:
	wstring name;
	Vec2 pos;
	Vec2 scale;
	vector<Component*> components;

	GameObject(const wstring& name, Vec2 pos, Vec2 Scale);
	~GameObject();

public:
	// [check] Level�� ������ �� �ְ�
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}
	void Render();

	static GameObject& Create(const wstring& name, Vec2 pos, Vec2 scale);
	void Destroy();

	template<typename T> requires std::derived_from<T, Component> void AddComponent();

public:
	// [check] Component �� ������ �� �ְ�
	GameObject(const GameObject& origin);

public:
	Vec2 GetPos() const { return pos; }
	Vec2 GetScale() const { return scale; }
	void SetPos(Vec2 pos) { this->pos = pos; }

	template<typename T> requires std::derived_from<T, Component> T* GetComponent();
};

// ���ӿ�����Ʈ ����
inline GameObject& GameObject::Create(const wstring& name, Vec2 pos, Vec2 scale)
{
	return *(new GameObject(name, pos, scale));
}

// ���ӿ�����Ʈ ����
inline void GameObject::Destroy()
{
	if (this != nullptr) delete this;
}

// ������Ʈ �߰�
template<typename T> requires std::derived_from<T, Component>
inline void GameObject::AddComponent()
{
	components.push_back(new T(this));
}

// ������Ʈ ��������
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::GetComponent()
{
	T* component = nullptr;

	// [check]
	// vector<Component*> �߿� T Ÿ���� ã�ƾ� ��
	for (auto item : components)
	{
		//if (typeid(item) == typeid(T*)) return (T*)item;
		component = static_cast<T*>(item);
		if (component != nullptr) return component;
	}

	return component;
}

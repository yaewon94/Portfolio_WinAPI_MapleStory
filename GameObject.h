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

	// [check] �̰� �Ķ���ͷ� �ѱ涧 new�� �����ؼ� ����� ���������� �Լ� ���ο��� �����Ҵ� �Ϸ��� �Ѱǵ�
	// �� �˲�� �ص� ���Ⱑ ����� AddComponent(new Player) �̷��� �Ѱܹ�����
	// AddComponent ���ο��� �Ķ���ͷ� �ѱ�� delete �ع����ڴ� �ٸ� ������Ʈ�� ������ �ִ� ������Ʈ �Ѱܹ�����
	// �� ������Ʈ ���������ϱ� �ȵŰ�
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(const T& component);
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(T&& component);

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
// @ param : �Ķ���Ϳ� �̹� ������ ��ü�� �ѱ� �� ���
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(const T& component)
{
	T* clone = nullptr;

	if (GetComponent<T>() != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, name + L"�� �̹� ������ �ִ� ������Ʈ �Դϴ� : " + ::to_wstring(typeid(T).name()));
	}
	else
	{
		clone = new T(component);
		components.push_back(clone);
	}

	return clone;
}

// ������Ʈ �߰�
// @ param : �ӽð�ü�� �Ķ���Ϳ� �ѱ� �� ���
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(T&& component)
{
	T* clone = nullptr;

	if (GetComponent<T>() != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, name + L"�� �̹� ������ �ִ� ������Ʈ �Դϴ� : " + ::to_wstring(typeid(T).name()));
	}
	else 
	{
		clone = new T(std::move(component));
		components.push_back(clone);
	}

	return clone;
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

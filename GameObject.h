#pragma once
#include "Entity.h"

class Component;

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
// abstract class
class GameObject : public Entity
{
#define ADD_COMPONENT(param) T* clone = nullptr;\
							if (GetComponent<T>() != nullptr)\
							{\
								Log(LOG_TYPE::LOG_ERROR, name + L"�� �̹� ������ �ִ� ������Ʈ �Դϴ� : " + ::to_wstring(typeid(T).name()));\
							}\
							else\
							{\
								clone = new T(param);\
								components.push_back(clone);\
							}\
							return clone;
private:
	vector<Component*> components;

protected:
	wstring name;
	Vec2 pos;
	Vec2 scale;

	GameObject(const wstring& name, Vec2 pos, Vec2 Scale);
	~GameObject();

public:
	CSTR_COPY_ASSIGN(GameObject);
	void Destroy();

	Vec2 GetPos() const { return pos; }
	Vec2 GetScale() const { return scale; }
	void SetPos(Vec2 pos) { this->pos = pos; }

	// [check] �ӽ�
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override;
	void Render();

	// [check] �̰� �Ķ���ͷ� �ѱ涧 new�� �����ؼ� ����� ���������� �Լ� ���ο��� �����Ҵ� �Ϸ��� �Ѱǵ�
	// �� �˲�� �ص� ���Ⱑ ����� AddComponent(new Player) �̷��� �Ѱܹ�����
	// AddComponent ���ο��� �Ķ���ͷ� �ѱ�� delete �ع����ڴ� �ٸ� ������Ʈ�� ������ �ִ� ������Ʈ �Ѱܹ�����
	// �� ������Ʈ ���������ϱ� �ȵŰ�
	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(const T& component);
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(T&& component);
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();
};

// ���ӿ�����Ʈ ����
inline void GameObject::Destroy()
{
	if (this != nullptr) delete this;
}

// ������Ʈ �߰�
// @ param : �⺻ �����ڷ� ������Ʈ�� �����ϰ� ���� �� ���
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent()
{
	ADD_COMPONENT(*this);
}

// ������Ʈ �߰�
// @ param : �Ķ���Ϳ� �̹� ������ ��ü�� �ѱ� �� ���
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(const T& component)
{
	ADD_COMPONENT(component);
}

// ������Ʈ �߰�
// @ param : �ӽð�ü�� �Ķ���Ϳ� �ѱ� �� ���
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(T&& component)
{
	ADD_COMPONENT(std::move(component));
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

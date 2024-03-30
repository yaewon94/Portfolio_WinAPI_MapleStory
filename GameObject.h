#pragma once
#include "Entity.h"

class Component;

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
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
	// [check] Level만 접근할 수 있게
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}
	void Render();

	static GameObject& Create(const wstring& name, Vec2 pos, Vec2 scale);
	void Destroy();

	template<typename T> requires std::derived_from<T, Component> void AddComponent();

public:
	// [check] Component 만 접근할 수 있게
	GameObject(const GameObject& origin);

public:
	Vec2 GetPos() const { return pos; }
	Vec2 GetScale() const { return scale; }
	void SetPos(Vec2 pos) { this->pos = pos; }

	template<typename T> requires std::derived_from<T, Component> T* GetComponent();
};

// 게임오브젝트 생성
inline GameObject& GameObject::Create(const wstring& name, Vec2 pos, Vec2 scale)
{
	return *(new GameObject(name, pos, scale));
}

// 게임오브젝트 삭제
inline void GameObject::Destroy()
{
	if (this != nullptr) delete this;
}

// 컴포넌트 추가
template<typename T> requires std::derived_from<T, Component>
inline void GameObject::AddComponent()
{
	components.push_back(new T(this));
}

// 컴포넌트 가져오기
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::GetComponent()
{
	T* component = nullptr;

	// [check]
	// vector<Component*> 중에 T 타입을 찾아야 함
	for (auto item : components)
	{
		//if (typeid(item) == typeid(T*)) return (T*)item;
		component = static_cast<T*>(item);
		if (component != nullptr) return component;
	}

	return component;
}

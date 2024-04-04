#pragma once
#include "Entity.h"

class Component;

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
// abstract class
class GameObject : public Entity
{
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
	void Destroy();
	virtual GameObject* Clone() = 0;

	Vec2 GetPos() const { return pos; }
	Vec2 GetScale() const { return scale; }
	LAYER_TYPE GetLayer() { return layer; }
	void SetPos(Vec2 pos) { this->pos = pos; }

	// [check] 임시
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override;
	void Render();

	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();

	// [check] CollisionManager에서만 호출할 수 있는 방법 없나 friend class 빼고
	virtual void OnCollisionEnter(GameObject& other) = 0;
	virtual void OnCollisionStay(GameObject& other) = 0;
	virtual void OnCollisionExit(GameObject& other) = 0;
};

// 게임오브젝트 삭제
inline void GameObject::Destroy()
{
	if (this != nullptr) delete this;
}

// 컴포넌트 추가
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent()
{
	T* clone = nullptr;

	if (GetComponent<T>() != nullptr)
	{
		Log(LOG_TYPE::LOG_ERROR, name + L"이 이미 가지고 있는 컴포넌트 입니다 : " + ::to_wstring(typeid(T).name())); \
	}
	else
	{
		clone = new T(*this); 
		components.push_back(clone); 
	}
	return clone;
}

// 컴포넌트 가져오기
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

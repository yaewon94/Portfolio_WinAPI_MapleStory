#pragma once
#include "Entity.h"

class Component;

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
// abstract class
class GameObject : public Entity
{
#define ADD_COMPONENT(param) T* clone = nullptr;\
							if (GetComponent<T>() != nullptr)\
							{\
								Log(LOG_TYPE::LOG_ERROR, name + L"이 이미 가지고 있는 컴포넌트 입니다 : " + ::to_wstring(typeid(T).name()));\
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

	// [check] 임시
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override;
	void Render();

	// [check] 이거 파라미터로 넘길때 new로 생성해서 만든거 지워버리고 함수 내부에서 동적할당 하려고 한건데
	// 뭔 똥꼬쇼를 해도 막기가 힘든듯 AddComponent(new Player) 이렇게 넘겨버리면
	// AddComponent 내부에서 파라미터로 넘긴거 delete 해버리자니 다른 오브젝트가 가지고 있는 컴포넌트 넘겨버리면
	// 그 컴포넌트 지워버리니까 안돼고
	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(const T& component);
	template<typename T> requires std::derived_from<T, Component> T* AddComponent(T&& component);
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();
};

// 게임오브젝트 삭제
inline void GameObject::Destroy()
{
	if (this != nullptr) delete this;
}

// 컴포넌트 추가
// @ param : 기본 생성자로 컴포넌트를 생성하고 싶을 때 사용
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent()
{
	ADD_COMPONENT(*this);
}

// 컴포넌트 추가
// @ param : 파라미터에 이미 선언한 객체를 넘길 때 사용
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(const T& component)
{
	ADD_COMPONENT(component);
}

// 컴포넌트 추가
// @ param : 임시객체를 파라미터에 넘길 때 사용
template<typename T> requires std::derived_from<T, Component>
inline T* GameObject::AddComponent(T&& component)
{
	ADD_COMPONENT(std::move(component));
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

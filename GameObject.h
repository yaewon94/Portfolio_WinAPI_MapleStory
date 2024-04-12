#pragma once
#include "Entity.h"

class Camera;
class Component;

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
// abstract class
class GameObject : public Entity
{
private:
	vector<Component*> components;
	LAYER_TYPE layer;
	GameObject* parent;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> children;
	bool isActive;

protected:
	wstring name;
	Vec2 offset;	// 부모 좌표를 기준으로 한 로컬좌표
	Vec2 scale;

	GameObject(const wstring& name, Vec2 pos, Vec2 Scale, LAYER_TYPE layer, bool isActive=true);
	GameObject(const GameObject& origin);
	~GameObject();

	void SetParent(GameObject& parent);
	GameObject* AddChild(GameObject& child);
	GameObject* AddChild(GameObject&& child);
	GameObject* GetChild(LAYER_TYPE layer) { return children[(size_t)layer].at(0); }

public:
	void Destroy() { if (this != nullptr) delete this; }
	virtual GameObject* Clone() = 0;

	Vec2 GetPos();			// 부모 offset + 자신 offset인 실제 좌표
	Vec2 GetRenderPos();	// 렌더링 좌표
	Vec2 GetScale() const { return scale; }
	LAYER_TYPE GetLayer() { return layer; }
	bool IsActive() const { return isActive; }

	void SetOffset(Vec2 offset) { this->offset = offset; }
	virtual void SetActive(bool flag) { isActive = flag; }

	// [check] 임시
	virtual void Init();
	virtual void Tick() {}
	virtual void FinalTick();
	void Render();

	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();

	// [check] CollisionManager에서만 호출할 수 있는 방법 없나 friend class 빼고
	virtual void OnCollisionEnter(GameObject& other) = 0;
	virtual void OnCollisionStay(GameObject& other) = 0;
	virtual void OnCollisionExit(GameObject& other) = 0;

private:
	void DeleteChildren();
};

// 좌표 반환
inline Vec2 GameObject::GetPos()
{
	if (parent == nullptr) return offset;
	return parent->GetPos() + offset;
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

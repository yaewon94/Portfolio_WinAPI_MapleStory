#pragma once
#include "Entity.h"

#define DEFAULT_OBJECT_POS Vec2(0.f, 0.f)		// 오브젝트 좌표 기본값
#define DEFAULT_OBJECT_SCALE  Vec2(100, 100)	// 오브젝트 크기 기본값

class Component;
class Texture;

// 플레이어, 몬스터, UI 등이 상속받는 최상위 클래스
// [abstract class]
class GameObject : public Entity
{
private:
	LAYER_TYPE layer;
	bool isActive = true;
	vector<Component*> components;
	Texture* texture;

	GameObject* parent;
	array<vector<GameObject*>, (size_t)LAYER_TYPE::LAYER_TYPE_COUNT> children;

protected:
	wstring name;
	Vec2<float> offset;	// 부모 좌표를 기준으로 한 로컬좌표 (오브젝트의 중심좌표 사용)
	Vec2<int> scale;

	GameObject(LAYER_TYPE layer);
	GameObject(const wstring& name, Vec2<float> offset, Vec2<int> Scale, LAYER_TYPE layer, bool isActive=true);
	GameObject(const GameObject& origin);
	~GameObject();

public:
	void Set(Vec2<float> offset, Vec2<int> scale);
	void SetScale(Vec2<int> scale) { this->scale = scale; }
	void SetTexture(Texture* texture) { this->texture = texture; }
	void SetParent(GameObject& parent);
	GameObject* AddChild(GameObject& child);
	GameObject* AddChild(GameObject&& child);
	GameObject* GetChild(LAYER_TYPE layer) { return children[(size_t)layer].at(0); }

	virtual GameObject* Clone() = 0;
	void Destroy() { if(this != nullptr) delete this; }

	Vec2<float> GetOffset() { return offset; }	// [테스트용]
	Vec2<float> GetRealPos();					// 부모 offset + 자신 offset인 실제 좌표
	virtual Vec2<float> GetRenderPos();		// 렌더링 좌표
	Vec2<int> GetScale() const { return scale; }
	LAYER_TYPE GetLayer() { return layer; }
	bool IsActive() const { return isActive; }
	Texture* GetTexture() { return texture; }
	GameObject* GetParent() { return parent; }

	void SetOffset(Vec2<float> offset) { this->offset = offset; }
	void SetRealPos(Vec2<float> pos);
	virtual void SetActive(bool flag);

	virtual void Init();
	virtual void Tick() {}
	virtual void FinalTick();
	virtual void Render();

	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();

	// [check] CollisionManager에서만 호출할 수 있는 방법 없나 friend class 빼고
	virtual void OnCollisionEnter(GameObject& other) {}
	virtual void OnCollisionStay(GameObject& other) {}
	virtual void OnCollisionExit(GameObject& other) {}

private:
	void DeleteChildren();
};

// 좌표 반환
inline Vec2<float> GameObject::GetRealPos()
{
	if (parent == nullptr) return offset;
	return parent->GetRealPos() + offset;
}

// 실제 좌표 설정 (리지드바디 같은 곳에서 필요)
inline void GameObject::SetRealPos(Vec2<float> pos)
{
	if (parent == nullptr) offset = pos;
	else offset = pos - parent->GetRealPos();
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

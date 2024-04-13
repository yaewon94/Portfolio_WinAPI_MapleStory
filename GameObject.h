#pragma once
#include "Entity.h"

class Camera;
class Component;

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
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
	Vec2<float> offset;	// �θ� ��ǥ�� �������� �� ������ǥ
	Vec2<int> scale;

	GameObject(const wstring& name, Vec2<float> offset, Vec2<int> Scale, LAYER_TYPE layer, bool isActive=true);
	GameObject(const GameObject& origin);
	~GameObject();

	void SetParent(GameObject& parent);
	GameObject* AddChild(GameObject& child);
	GameObject* AddChild(GameObject&& child);
	GameObject* GetChild(LAYER_TYPE layer) { return children[(size_t)layer].at(0); }

public:
	void Destroy() { if (this != nullptr) delete this; }
	virtual GameObject* Clone() = 0;

	Vec2<float> GetPos();			// �θ� offset + �ڽ� offset�� ���� ��ǥ
	Vec2<float> GetRenderPos();		// ������ ��ǥ
	Vec2<int> GetScale() const { return scale; }
	LAYER_TYPE GetLayer() { return layer; }
	bool IsActive() const { return isActive; }

	GameObject* GetParent() { return parent; }

	void SetOffset(Vec2<float> offset) { this->offset = offset; }
	virtual void SetActive(bool flag) { isActive = flag; }

	// [check] �ӽ�
	virtual void Init();
	virtual void Tick() {}
	virtual void FinalTick();
	void Render();

	template<typename T> requires std::derived_from<T, Component> T* AddComponent();
	template<typename T> requires std::derived_from<T, Component> T* GetComponent();

	// [check] CollisionManager������ ȣ���� �� �ִ� ��� ���� friend class ����
	virtual void OnCollisionEnter(GameObject& other) = 0;
	virtual void OnCollisionStay(GameObject& other) = 0;
	virtual void OnCollisionExit(GameObject& other) = 0;

private:
	void DeleteChildren();
};

// ��ǥ ��ȯ
inline Vec2<float> GameObject::GetPos()
{
	if (parent == nullptr) return offset;
	return parent->GetPos() + offset;
}

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

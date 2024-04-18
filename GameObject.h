#pragma once
#include "Entity.h"

#define DEFAULT_OBJECT_POS Vec2(0.f, 0.f)		// ������Ʈ ��ǥ �⺻��
#define DEFAULT_OBJECT_SCALE  Vec2(100, 100)	// ������Ʈ ũ�� �⺻��

class Component;
class Texture;

// �÷��̾�, ����, UI ���� ��ӹ޴� �ֻ��� Ŭ����
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
	Vec2<float> offset;	// �θ� ��ǥ�� �������� �� ������ǥ (������Ʈ�� �߽���ǥ ���)
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

	Vec2<float> GetOffset() { return offset; }	// [�׽�Ʈ��]
	Vec2<float> GetRealPos();					// �θ� offset + �ڽ� offset�� ���� ��ǥ
	virtual Vec2<float> GetRenderPos();		// ������ ��ǥ
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

	// [check] CollisionManager������ ȣ���� �� �ִ� ��� ���� friend class ����
	virtual void OnCollisionEnter(GameObject& other) {}
	virtual void OnCollisionStay(GameObject& other) {}
	virtual void OnCollisionExit(GameObject& other) {}

private:
	void DeleteChildren();
};

// ��ǥ ��ȯ
inline Vec2<float> GameObject::GetRealPos()
{
	if (parent == nullptr) return offset;
	return parent->GetRealPos() + offset;
}

// ���� ��ǥ ���� (������ٵ� ���� ������ �ʿ�)
inline void GameObject::SetRealPos(Vec2<float> pos)
{
	if (parent == nullptr) offset = pos;
	else offset = pos - parent->GetRealPos();
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

#pragma once
#include "Entity.h"

class GameObject;

// ���� ������Ʈ�� ������ �ִ� ������Ʈ �ֻ��� Ŭ����
// abstract class
class Component : public Entity
{
private:
	GameObject* owner;

protected:
	Component(GameObject& owner);
	Component(const Component& origin);
	~Component();

public:
	void Destroy();
	virtual Component* Clone() = 0;

	GameObject* GetOwner() const { return owner; }

	// [check] �ӽ�
	virtual void Init() override {}
	virtual void Tick() override {}
	virtual void FinalTick() override {}
};

// ������Ʈ ����
inline void Component::Destroy()
{
	if (this != nullptr) delete this;
}
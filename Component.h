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
	CSTR_COPY_ASSIGN(Component);
	Component(GameObject& owner);
	~Component();

public:
	void Destroy();
	virtual Component* Clone() = 0;

	GameObject* GetOwner() { return owner; }

	// [check] �ӽ�
	virtual void Init() override {}
	virtual void Tick() override {}
};

// ������Ʈ ����
inline void Component::Destroy()
{
	if (this != nullptr) delete this;
}
#pragma once
#include "Entity.h"

class GameObject;

// ���� ������Ʈ�� ������ �ִ� ������Ʈ �ֻ��� Ŭ����
// abstract class
class Component : public Entity
{
private:
	GameObject* owner;

public:
	Component(GameObject& owner);
	Component(const Component& origin);
	Component(Component&& origin) noexcept;
	~Component();

	Component& operator=(const Component& origin);
	Component& operator=(Component&& origin) noexcept;
	virtual Component* Clone() = 0;

	GameObject* GetOwner() { return owner; }
};